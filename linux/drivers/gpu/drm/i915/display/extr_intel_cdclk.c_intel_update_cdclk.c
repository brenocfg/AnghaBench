#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cdclk; } ;
struct TYPE_5__ {TYPE_3__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_cdclk ) (struct drm_i915_private*,TYPE_3__*) ;} ;
struct drm_i915_private {TYPE_2__ cdclk; TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GMBUSFREQ_VLV ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,TYPE_3__*) ; 

void intel_update_cdclk(struct drm_i915_private *dev_priv)
{
	dev_priv->display.get_cdclk(dev_priv, &dev_priv->cdclk.hw);

	/*
	 * 9:0 CMBUS [sic] CDCLK frequency (cdfreq):
	 * Programmng [sic] note: bit[9:2] should be programmed to the number
	 * of cdclk that generates 4MHz reference clock freq which is used to
	 * generate GMBus clock. This will vary with the cdclk freq.
	 */
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		I915_WRITE(GMBUSFREQ_VLV,
			   DIV_ROUND_UP(dev_priv->cdclk.hw.cdclk, 1000));
}