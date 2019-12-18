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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apb_ctrl_poweroff (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ usb3613_hub_mode_ctrl (int) ; 

__attribute__((used)) static int apb_poweroff(struct device *dev, void *data)
{
	apb_ctrl_poweroff(dev);

	/* Enable HUB3613 into HUB mode. */
	if (usb3613_hub_mode_ctrl(false))
		dev_warn(dev, "failed to control hub device\n");

	return 0;
}