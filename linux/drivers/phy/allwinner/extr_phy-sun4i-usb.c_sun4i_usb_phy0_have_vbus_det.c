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
struct sun4i_usb_phy_data {scalar_t__ vbus_power_supply; scalar_t__ vbus_det_gpio; } ;

/* Variables and functions */

__attribute__((used)) static bool sun4i_usb_phy0_have_vbus_det(struct sun4i_usb_phy_data *data)
{
	return data->vbus_det_gpio || data->vbus_power_supply;
}