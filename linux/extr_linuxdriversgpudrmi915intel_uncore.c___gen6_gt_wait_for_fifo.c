#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ fifo_count; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 scalar_t__ GT_FIFO_NUM_RESERVED_ENTRIES ; 
 int /*<<< orphan*/  GT_FIFO_TIMEOUT_MS ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 scalar_t__ fifo_free_entries (struct drm_i915_private*) ; 
 scalar_t__ wait_for_atomic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gen6_gt_wait_for_fifo(struct drm_i915_private *dev_priv)
{
	u32 n;

	/* On VLV, FIFO will be shared by both SW and HW.
	 * So, we need to read the FREE_ENTRIES everytime */
	if (IS_VALLEYVIEW(dev_priv))
		n = fifo_free_entries(dev_priv);
	else
		n = dev_priv->uncore.fifo_count;

	if (n <= GT_FIFO_NUM_RESERVED_ENTRIES) {
		if (wait_for_atomic((n = fifo_free_entries(dev_priv)) >
				    GT_FIFO_NUM_RESERVED_ENTRIES,
				    GT_FIFO_TIMEOUT_MS)) {
			DRM_DEBUG("GT_FIFO timeout, entries: %u\n", n);
			return;
		}
	}

	dev_priv->uncore.fifo_count = n - 1;
}