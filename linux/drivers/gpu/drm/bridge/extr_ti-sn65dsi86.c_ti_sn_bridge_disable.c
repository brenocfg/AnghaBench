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
struct ti_sn_bridge {int /*<<< orphan*/  panel; int /*<<< orphan*/  regmap; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SN_ENH_FRAME_REG ; 
 int /*<<< orphan*/  SN_ML_TX_MODE_REG ; 
 int /*<<< orphan*/  SN_PLL_ENABLE_REG ; 
 int /*<<< orphan*/  VSTREAM_ENABLE ; 
 struct ti_sn_bridge* bridge_to_ti_sn_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sn_bridge_disable(struct drm_bridge *bridge)
{
	struct ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);

	drm_panel_disable(pdata->panel);

	/* disable video stream */
	regmap_update_bits(pdata->regmap, SN_ENH_FRAME_REG, VSTREAM_ENABLE, 0);
	/* semi auto link training mode OFF */
	regmap_write(pdata->regmap, SN_ML_TX_MODE_REG, 0);
	/* disable DP PLL */
	regmap_write(pdata->regmap, SN_PLL_ENABLE_REG, 0);

	drm_panel_unprepare(pdata->panel);
}