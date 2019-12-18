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
struct TYPE_2__ {int stride; } ;
struct intel_fbc_state_cache {TYPE_1__ fb; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_fbc_get_plane_source_size (struct intel_fbc_state_cache*,int /*<<< orphan*/ *,int*) ; 
 int min (int,int) ; 

__attribute__((used)) static int intel_fbc_calculate_cfb_size(struct drm_i915_private *dev_priv,
					struct intel_fbc_state_cache *cache)
{
	int lines;

	intel_fbc_get_plane_source_size(cache, NULL, &lines);
	if (IS_GEN(dev_priv, 7))
		lines = min(lines, 2048);
	else if (INTEL_GEN(dev_priv) >= 8)
		lines = min(lines, 2560);

	/* Hardware needs the full buffer stride, not just the active area. */
	return lines * cache->fb.stride;
}