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
typedef  int u8 ;
struct da9150_charger {int /*<<< orphan*/ * battery; int /*<<< orphan*/ * usb; int /*<<< orphan*/ * supply_online; int /*<<< orphan*/  dev; int /*<<< orphan*/  da9150; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_STATUS_H ; 
#define  DA9150_VBUS_STAT_CHG 130 
 int DA9150_VBUS_STAT_MASK ; 
#define  DA9150_VBUS_STAT_OFF 129 
#define  DA9150_VBUS_STAT_WAIT 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int da9150_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t da9150_charger_vbus_irq(int irq, void *data)
{
	struct da9150_charger *charger = data;
	u8 reg;

	reg = da9150_reg_read(charger->da9150, DA9150_STATUS_H);

	/* Charger plugged in or battery only */
	switch (reg & DA9150_VBUS_STAT_MASK) {
	case DA9150_VBUS_STAT_OFF:
	case DA9150_VBUS_STAT_WAIT:
		charger->supply_online = charger->battery;
		break;
	case DA9150_VBUS_STAT_CHG:
		charger->supply_online = charger->usb;
		break;
	default:
		dev_warn(charger->dev, "Unknown VBUS state - reg = 0x%x\n",
			 reg);
		charger->supply_online = NULL;
		break;
	}

	power_supply_changed(charger->usb);
	power_supply_changed(charger->battery);

	return IRQ_HANDLED;
}