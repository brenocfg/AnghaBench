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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ dev; } ;
struct tc_data {scalar_t__ hpd_pin; int /*<<< orphan*/  regmap; TYPE_1__ bridge; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSTS_G ; 
 int INT_GPIO_H (scalar_t__) ; 
 int INT_GPIO_LC (scalar_t__) ; 
 int INT_SYSERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SYSSTAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (scalar_t__) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t tc_irq_handler(int irq, void *arg)
{
	struct tc_data *tc = arg;
	u32 val;
	int r;

	r = regmap_read(tc->regmap, INTSTS_G, &val);
	if (r)
		return IRQ_NONE;

	if (!val)
		return IRQ_NONE;

	if (val & INT_SYSERR) {
		u32 stat = 0;

		regmap_read(tc->regmap, SYSSTAT, &stat);

		dev_err(tc->dev, "syserr %x\n", stat);
	}

	if (tc->hpd_pin >= 0 && tc->bridge.dev) {
		/*
		 * H is triggered when the GPIO goes high.
		 *
		 * LC is triggered when the GPIO goes low and stays low for
		 * the duration of LCNT
		 */
		bool h = val & INT_GPIO_H(tc->hpd_pin);
		bool lc = val & INT_GPIO_LC(tc->hpd_pin);

		dev_dbg(tc->dev, "GPIO%d: %s %s\n", tc->hpd_pin,
			h ? "H" : "", lc ? "LC" : "");

		if (h || lc)
			drm_kms_helper_hotplug_event(tc->bridge.dev);
	}

	regmap_write(tc->regmap, INTSTS_G, val);

	return IRQ_HANDLED;
}