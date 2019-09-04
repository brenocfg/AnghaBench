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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_GMCH_DISPLAY (struct drm_i915_private*) ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int drm_format_plane_cpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static
u32 intel_fb_pitch_limit(struct drm_i915_private *dev_priv,
			 uint64_t fb_modifier, uint32_t pixel_format)
{
	u32 gen = INTEL_GEN(dev_priv);

	if (gen >= 9) {
		int cpp = drm_format_plane_cpp(pixel_format, 0);

		/* "The stride in bytes must not exceed the of the size of 8K
		 *  pixels and 32K bytes."
		 */
		return min(8192 * cpp, 32768);
	} else if (gen >= 5 && !HAS_GMCH_DISPLAY(dev_priv)) {
		return 32*1024;
	} else if (gen >= 4) {
		if (fb_modifier == I915_FORMAT_MOD_X_TILED)
			return 16*1024;
		else
			return 32*1024;
	} else if (gen >= 3) {
		if (fb_modifier == I915_FORMAT_MOD_X_TILED)
			return 8*1024;
		else
			return 16*1024;
	} else {
		/* XXX DSPC is limited to 4k tiled */
		return 8*1024;
	}
}