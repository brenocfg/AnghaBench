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
struct hdmi_context {int powered; int /*<<< orphan*/  dev; int /*<<< orphan*/  regul_bulk; int /*<<< orphan*/  pmureg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_CON_0 ; 
 int /*<<< orphan*/  HDMI_EN ; 
 int /*<<< orphan*/  HDMI_PHY_CON_0 ; 
 int /*<<< orphan*/  HDMI_PHY_POWER_OFF_EN ; 
 int /*<<< orphan*/  PMU_HDMI_PHY_CONTROL ; 
 int /*<<< orphan*/  PMU_HDMI_PHY_ENABLE_BIT ; 
 int /*<<< orphan*/  hdmi_reg_writemask (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_set_refclk (struct hdmi_context*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply ; 

__attribute__((used)) static void hdmiphy_disable(struct hdmi_context *hdata)
{
	if (!hdata->powered)
		return;

	hdmi_reg_writemask(hdata, HDMI_CON_0, 0, HDMI_EN);

	hdmi_reg_writemask(hdata, HDMI_PHY_CON_0, ~0, HDMI_PHY_POWER_OFF_EN);

	hdmi_set_refclk(hdata, false);

	regmap_update_bits(hdata->pmureg, PMU_HDMI_PHY_CONTROL,
			PMU_HDMI_PHY_ENABLE_BIT, 0);

	regulator_bulk_disable(ARRAY_SIZE(supply), hdata->regul_bulk);

	pm_runtime_put_sync(hdata->dev);

	hdata->powered = false;
}