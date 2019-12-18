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
struct stih407_usb2_picophy {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STIH407_USB_PICOPHY_CTRL_PORT_CONF ; 
 int /*<<< orphan*/  STIH407_USB_PICOPHY_CTRL_PORT_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stih407_usb2_pico_ctrl(struct stih407_usb2_picophy *phy_dev)
{
	reset_control_deassert(phy_dev->rstc);

	return regmap_update_bits(phy_dev->regmap, phy_dev->ctrl,
				  STIH407_USB_PICOPHY_CTRL_PORT_MASK,
				  STIH407_USB_PICOPHY_CTRL_PORT_CONF);
}