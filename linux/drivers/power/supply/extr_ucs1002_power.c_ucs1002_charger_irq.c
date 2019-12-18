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
struct ucs1002_info {int present; int /*<<< orphan*/  charger; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int F_ADET_PIN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UCS1002_REG_OTHER_STATUS ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t ucs1002_charger_irq(int irq, void *data)
{
	int ret, regval;
	bool present;
	struct ucs1002_info *info = data;

	present = info->present;

	ret = regmap_read(info->regmap, UCS1002_REG_OTHER_STATUS, &regval);
	if (ret)
		return IRQ_HANDLED;

	/* update attached status */
	info->present = regval & F_ADET_PIN;

	/* notify the change */
	if (present != info->present)
		power_supply_changed(info->charger);

	return IRQ_HANDLED;
}