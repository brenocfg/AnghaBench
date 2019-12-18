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
struct device {int dummy; } ;
struct da8xx_ohci_hcd {scalar_t__ vbus_reg; int /*<<< orphan*/  oc_gpio; TYPE_2__* hcd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct device* controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static irqreturn_t ohci_da8xx_oc_thread(int irq, void *data)
{
	struct da8xx_ohci_hcd *da8xx_ohci = data;
	struct device *dev = da8xx_ohci->hcd->self.controller;
	int ret;

	if (gpiod_get_value_cansleep(da8xx_ohci->oc_gpio) &&
	    da8xx_ohci->vbus_reg) {
		ret = regulator_disable(da8xx_ohci->vbus_reg);
		if (ret)
			dev_err(dev, "Failed to disable regulator: %d\n", ret);
	}

	return IRQ_HANDLED;
}