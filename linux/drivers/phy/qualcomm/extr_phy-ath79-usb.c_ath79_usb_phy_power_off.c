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
struct phy {int dummy; } ;
struct ath79_usb_phy {scalar_t__ reset; scalar_t__ no_suspend_override; } ;

/* Variables and functions */
 struct ath79_usb_phy* phy_get_drvdata (struct phy*) ; 
 int reset_control_assert (scalar_t__) ; 
 int reset_control_deassert (scalar_t__) ; 

__attribute__((used)) static int ath79_usb_phy_power_off(struct phy *phy)
{
	struct ath79_usb_phy *priv = phy_get_drvdata(phy);
	int err = 0;

	err = reset_control_assert(priv->reset);
	if (err)
		return err;

	if (priv->no_suspend_override) {
		err = reset_control_deassert(priv->no_suspend_override);
		if (err)
			reset_control_deassert(priv->reset);
	}

	return err;
}