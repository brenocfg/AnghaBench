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
struct sun4i_usb_phy_data {int /*<<< orphan*/  detect; scalar_t__ vbus_det; } ;
struct sun4i_usb_phy {int regulator_on; scalar_t__ index; int /*<<< orphan*/  vbus; } ;
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBOUNCE_TIME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sun4i_usb_phy* phy_get_drvdata (struct phy*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ sun4i_usb_phy0_have_vbus_det (struct sun4i_usb_phy_data*) ; 
 scalar_t__ sun4i_usb_phy0_poll (struct sun4i_usb_phy_data*) ; 
 int /*<<< orphan*/  system_wq ; 
 struct sun4i_usb_phy_data* to_sun4i_usb_phy_data (struct sun4i_usb_phy*) ; 

__attribute__((used)) static int sun4i_usb_phy_power_on(struct phy *_phy)
{
	struct sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	struct sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	int ret;

	if (!phy->vbus || phy->regulator_on)
		return 0;

	/* For phy0 only turn on Vbus if we don't have an ext. Vbus */
	if (phy->index == 0 && sun4i_usb_phy0_have_vbus_det(data) &&
				data->vbus_det) {
		dev_warn(&_phy->dev, "External vbus detected, not enabling our own vbus\n");
		return 0;
	}

	ret = regulator_enable(phy->vbus);
	if (ret)
		return ret;

	phy->regulator_on = true;

	/* We must report Vbus high within OTG_TIME_A_WAIT_VRISE msec. */
	if (phy->index == 0 && sun4i_usb_phy0_poll(data))
		mod_delayed_work(system_wq, &data->detect, DEBOUNCE_TIME);

	return 0;
}