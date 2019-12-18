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
struct sun4i_usb_phy_data {int /*<<< orphan*/  detect; } ;
struct sun4i_usb_phy {int regulator_on; scalar_t__ index; int /*<<< orphan*/  vbus; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_TIME ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sun4i_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_usb_phy0_poll (struct sun4i_usb_phy_data*) ; 
 int /*<<< orphan*/  system_wq ; 
 struct sun4i_usb_phy_data* to_sun4i_usb_phy_data (struct sun4i_usb_phy*) ; 

__attribute__((used)) static int sun4i_usb_phy_power_off(struct phy *_phy)
{
	struct sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	struct sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);

	if (!phy->vbus || !phy->regulator_on)
		return 0;

	regulator_disable(phy->vbus);
	phy->regulator_on = false;

	/*
	 * phy0 vbus typically slowly discharges, sometimes this causes the
	 * Vbus gpio to not trigger an edge irq on Vbus off, so force a rescan.
	 */
	if (phy->index == 0 && !sun4i_usb_phy0_poll(data))
		mod_delayed_work(system_wq, &data->detect, POLL_TIME);

	return 0;
}