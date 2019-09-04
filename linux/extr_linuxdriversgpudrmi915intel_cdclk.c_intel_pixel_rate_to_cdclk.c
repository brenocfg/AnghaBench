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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

__attribute__((used)) static int intel_pixel_rate_to_cdclk(struct drm_i915_private *dev_priv,
				     int pixel_rate)
{
	if (INTEL_GEN(dev_priv) >= 10)
		return DIV_ROUND_UP(pixel_rate, 2);
	else if (IS_GEMINILAKE(dev_priv))
		/*
		 * FIXME: Avoid using a pixel clock that is more than 99% of the cdclk
		 * as a temporary workaround. Use a higher cdclk instead. (Note that
		 * intel_compute_max_dotclk() limits the max pixel clock to 99% of max
		 * cdclk.)
		 */
		return DIV_ROUND_UP(pixel_rate * 100, 2 * 99);
	else if (IS_GEN9(dev_priv) ||
		 IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		return pixel_rate;
	else if (IS_CHERRYVIEW(dev_priv))
		return DIV_ROUND_UP(pixel_rate * 100, 95);
	else
		return DIV_ROUND_UP(pixel_rate * 100, 90);
}