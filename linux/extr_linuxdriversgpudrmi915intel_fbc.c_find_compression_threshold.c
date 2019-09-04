#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct drm_mm_node {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  dsm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ U64_MAX ; 
 int i915_gem_stolen_insert_node_in_range (struct drm_i915_private*,struct drm_mm_node*,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ resource_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_compression_threshold(struct drm_i915_private *dev_priv,
				      struct drm_mm_node *node,
				      int size,
				      int fb_cpp)
{
	int compression_threshold = 1;
	int ret;
	u64 end;

	/* The FBC hardware for BDW/SKL doesn't have access to the stolen
	 * reserved range size, so it always assumes the maximum (8mb) is used.
	 * If we enable FBC using a CFB on that memory range we'll get FIFO
	 * underruns, even if that range is not reserved by the BIOS. */
	if (IS_BROADWELL(dev_priv) || IS_GEN9_BC(dev_priv))
		end = resource_size(&dev_priv->dsm) - 8 * 1024 * 1024;
	else
		end = U64_MAX;

	/* HACK: This code depends on what we will do in *_enable_fbc. If that
	 * code changes, this code needs to change as well.
	 *
	 * The enable_fbc code will attempt to use one of our 2 compression
	 * thresholds, therefore, in that case, we only have 1 resort.
	 */

	/* Try to over-allocate to reduce reallocations and fragmentation. */
	ret = i915_gem_stolen_insert_node_in_range(dev_priv, node, size <<= 1,
						   4096, 0, end);
	if (ret == 0)
		return compression_threshold;

again:
	/* HW's ability to limit the CFB is 1:4 */
	if (compression_threshold > 4 ||
	    (fb_cpp == 2 && compression_threshold == 2))
		return 0;

	ret = i915_gem_stolen_insert_node_in_range(dev_priv, node, size >>= 1,
						   4096, 0, end);
	if (ret && INTEL_GEN(dev_priv) <= 4) {
		return 0;
	} else if (ret) {
		compression_threshold <<= 1;
		goto again;
	} else {
		return compression_threshold;
	}
}