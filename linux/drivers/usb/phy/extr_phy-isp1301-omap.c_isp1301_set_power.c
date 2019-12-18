#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_phy {TYPE_1__* otg; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OTG_STATE_B_PERIPHERAL ; 
 int /*<<< orphan*/  enable_vbus_draw (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  the_transceiver ; 

__attribute__((used)) static int
isp1301_set_power(struct usb_phy *dev, unsigned mA)
{
	if (!the_transceiver)
		return -ENODEV;
	if (dev->otg->state == OTG_STATE_B_PERIPHERAL)
		enable_vbus_draw(the_transceiver, mA);
	return 0;
}