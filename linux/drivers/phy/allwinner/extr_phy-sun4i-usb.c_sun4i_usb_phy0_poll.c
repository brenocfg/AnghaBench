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
struct sun4i_usb_phy_data {scalar_t__ id_det_irq; scalar_t__ vbus_det_irq; TYPE_1__* phys; scalar_t__ vbus_power_supply; TYPE_2__* cfg; scalar_t__ vbus_det_gpio; scalar_t__ id_det_gpio; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ regulator_on; } ;

/* Variables and functions */
 scalar_t__ sun6i_a31_phy ; 
 scalar_t__ sun8i_a33_phy ; 

__attribute__((used)) static bool sun4i_usb_phy0_poll(struct sun4i_usb_phy_data *data)
{
	if ((data->id_det_gpio && data->id_det_irq <= 0) ||
	    (data->vbus_det_gpio && data->vbus_det_irq <= 0))
		return true;

	/*
	 * The A31/A23/A33 companion pmics (AXP221/AXP223) do not
	 * generate vbus change interrupts when the board is driving
	 * vbus using the N_VBUSEN pin on the pmic, so we must poll
	 * when using the pmic for vbus-det _and_ we're driving vbus.
	 */
	if ((data->cfg->type == sun6i_a31_phy ||
	     data->cfg->type == sun8i_a33_phy) &&
	    data->vbus_power_supply && data->phys[0].regulator_on)
		return true;

	return false;
}