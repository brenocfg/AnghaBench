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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int intel_plane_fb_max_stride (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ccs_modifier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
u32 intel_fb_max_stride(struct drm_i915_private *dev_priv,
			u32 pixel_format, u64 modifier)
{
	/*
	 * Arbitrary limit for gen4+ chosen to match the
	 * render engine max stride.
	 *
	 * The new CCS hash mode makes remapping impossible
	 */
	if (!is_ccs_modifier(modifier)) {
		if (INTEL_GEN(dev_priv) >= 7)
			return 256*1024;
		else if (INTEL_GEN(dev_priv) >= 4)
			return 128*1024;
	}

	return intel_plane_fb_max_stride(dev_priv, pixel_format, modifier);
}