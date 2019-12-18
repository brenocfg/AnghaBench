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
struct ti_sn_bridge {int /*<<< orphan*/  panel; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPD_DISABLE ; 
 int /*<<< orphan*/  SN_HPD_DISABLE_REG ; 
 struct ti_sn_bridge* bridge_to_ti_sn_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sn_bridge_set_refclk_freq (struct ti_sn_bridge*) ; 

__attribute__((used)) static void ti_sn_bridge_pre_enable(struct drm_bridge *bridge)
{
	struct ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);

	pm_runtime_get_sync(pdata->dev);

	/* configure bridge ref_clk */
	ti_sn_bridge_set_refclk_freq(pdata);

	/*
	 * HPD on this bridge chip is a bit useless.  This is an eDP bridge
	 * so the HPD is an internal signal that's only there to signal that
	 * the panel is done powering up.  ...but the bridge chip debounces
	 * this signal by between 100 ms and 400 ms (depending on process,
	 * voltage, and temperate--I measured it at about 200 ms).  One
	 * particular panel asserted HPD 84 ms after it was powered on meaning
	 * that we saw HPD 284 ms after power on.  ...but the same panel said
	 * that instead of looking at HPD you could just hardcode a delay of
	 * 200 ms.  We'll assume that the panel driver will have the hardcoded
	 * delay in its prepare and always disable HPD.
	 *
	 * If HPD somehow makes sense on some future panel we'll have to
	 * change this to be conditional on someone specifying that HPD should
	 * be used.
	 */
	regmap_update_bits(pdata->regmap, SN_HPD_DISABLE_REG, HPD_DISABLE,
			   HPD_DISABLE);

	drm_panel_prepare(pdata->panel);
}