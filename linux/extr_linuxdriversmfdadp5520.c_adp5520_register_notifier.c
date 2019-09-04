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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;
struct adp5520_chip {int /*<<< orphan*/  notifier_list; int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 unsigned int ADP5520_CMPR_IEN ; 
 int /*<<< orphan*/  ADP5520_INTERRUPT_ENABLE ; 
 unsigned int ADP5520_KP_IEN ; 
 unsigned int ADP5520_KR_IEN ; 
 unsigned int ADP5520_OVP_IEN ; 
 int ENODEV ; 
 int /*<<< orphan*/  adp5520_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 struct adp5520_chip* dev_get_drvdata (struct device*) ; 

int adp5520_register_notifier(struct device *dev, struct notifier_block *nb,
				unsigned int events)
{
	struct adp5520_chip *chip = dev_get_drvdata(dev);

	if (chip->irq) {
		adp5520_set_bits(chip->dev, ADP5520_INTERRUPT_ENABLE,
			events & (ADP5520_KP_IEN | ADP5520_KR_IEN |
			ADP5520_OVP_IEN | ADP5520_CMPR_IEN));

		return blocking_notifier_chain_register(&chip->notifier_list,
			 nb);
	}

	return -ENODEV;
}