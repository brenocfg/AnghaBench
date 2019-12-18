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
struct hdmi_context {int powered; int /*<<< orphan*/  pmureg; int /*<<< orphan*/  dev; int /*<<< orphan*/  regul_bulk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HDMI_PHY_CON_0 ; 
 int /*<<< orphan*/  HDMI_PHY_POWER_OFF_EN ; 
 int /*<<< orphan*/  PMU_HDMI_PHY_CONTROL ; 
 int /*<<< orphan*/  PMU_HDMI_PHY_ENABLE_BIT ; 
 int /*<<< orphan*/  hdmi_reg_writemask (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_set_refclk (struct hdmi_context*,int) ; 
 int /*<<< orphan*/  hdmiphy_conf_apply (struct hdmi_context*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply ; 

__attribute__((used)) static void hdmiphy_enable(struct hdmi_context *hdata)
{
	if (hdata->powered)
		return;

	pm_runtime_get_sync(hdata->dev);

	if (regulator_bulk_enable(ARRAY_SIZE(supply), hdata->regul_bulk))
		DRM_DEV_DEBUG_KMS(hdata->dev,
				  "failed to enable regulator bulk\n");

	regmap_update_bits(hdata->pmureg, PMU_HDMI_PHY_CONTROL,
			PMU_HDMI_PHY_ENABLE_BIT, 1);

	hdmi_set_refclk(hdata, true);

	hdmi_reg_writemask(hdata, HDMI_PHY_CON_0, 0, HDMI_PHY_POWER_OFF_EN);

	hdmiphy_conf_apply(hdata);

	hdata->powered = true;
}