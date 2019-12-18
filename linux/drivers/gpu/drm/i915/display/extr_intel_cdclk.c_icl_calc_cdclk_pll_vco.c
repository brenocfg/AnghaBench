#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bypass; int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int icl_calc_cdclk_pll_vco(struct drm_i915_private *dev_priv, int cdclk)
{
	int ratio;

	if (cdclk == dev_priv->cdclk.hw.bypass)
		return 0;

	switch (cdclk) {
	default:
		MISSING_CASE(cdclk);
		/* fall through */
	case 172800:
	case 307200:
	case 556800:
	case 652800:
		WARN_ON(dev_priv->cdclk.hw.ref != 19200 &&
			dev_priv->cdclk.hw.ref != 38400);
		break;
	case 180000:
	case 312000:
	case 552000:
	case 648000:
		WARN_ON(dev_priv->cdclk.hw.ref != 24000);
		break;
	case 192000:
		WARN_ON(dev_priv->cdclk.hw.ref != 19200 &&
			dev_priv->cdclk.hw.ref != 38400 &&
			dev_priv->cdclk.hw.ref != 24000);
		break;
	}

	ratio = cdclk / (dev_priv->cdclk.hw.ref / 2);

	return dev_priv->cdclk.hw.ref * ratio;
}