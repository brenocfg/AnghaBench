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
struct rt9455_info {int /*<<< orphan*/ * regmap_fields; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_BST32SI ; 
 int /*<<< orphan*/  F_BSTBUSOVI ; 
 int /*<<< orphan*/  F_BSTLOWVI ; 
 int /*<<< orphan*/  F_BSTOLI ; 
 size_t F_OPA_MODE ; 
 unsigned int GET_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT9455_CHARGE_MODE ; 
 int /*<<< orphan*/  RT9455_REG_IRQ3 ; 
 int /*<<< orphan*/  RT9455_REG_MASK3 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int rt9455_set_voreg_before_charge_mode (struct rt9455_info*) ; 

__attribute__((used)) static int rt9455_irq_handler_check_irq3_register(struct rt9455_info *info,
						  bool *_alert_userspace)
{
	unsigned int irq3, mask3;
	struct device *dev = &info->client->dev;
	bool alert_userspace = false;
	int ret;

	ret = regmap_read(info->regmap, RT9455_REG_IRQ3, &irq3);
	if (ret) {
		dev_err(dev, "Failed to read IRQ3 register\n");
		return ret;
	}

	ret = regmap_read(info->regmap, RT9455_REG_MASK3, &mask3);
	if (ret) {
		dev_err(dev, "Failed to read MASK3 register\n");
		return ret;
	}

	if (irq3 & GET_MASK(F_BSTBUSOVI)) {
		dev_err(dev, "Boost fault. Overvoltage input occurred\n");
		alert_userspace = true;
	}
	if (irq3 & GET_MASK(F_BSTOLI)) {
		dev_err(dev, "Boost fault. Overload\n");
		alert_userspace = true;
	}
	if (irq3 & GET_MASK(F_BSTLOWVI)) {
		dev_err(dev, "Boost fault. Battery voltage too low\n");
		alert_userspace = true;
	}
	if (irq3 & GET_MASK(F_BST32SI)) {
		dev_err(dev, "Boost fault. 32 seconds timeout occurred.\n");
		alert_userspace = true;
	}

	if (alert_userspace) {
		dev_info(dev, "Boost fault occurred, therefore the charger goes into charge mode\n");
		ret = rt9455_set_voreg_before_charge_mode(info);
		if (ret) {
			dev_err(dev, "Failed to set VOREG before entering charge mode\n");
			return ret;
		}
		ret = regmap_field_write(info->regmap_fields[F_OPA_MODE],
					 RT9455_CHARGE_MODE);
		if (ret) {
			dev_err(dev, "Failed to set charger in charge mode\n");
			return ret;
		}
		*_alert_userspace = alert_userspace;
	}

	return 0;
}