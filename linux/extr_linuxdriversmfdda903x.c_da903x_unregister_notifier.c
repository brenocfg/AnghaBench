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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;
struct da903x_chip {int /*<<< orphan*/  notifier_list; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mask_events ) (struct da903x_chip*,unsigned int) ;} ;

/* Variables and functions */
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 struct da903x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct da903x_chip*,unsigned int) ; 

int da903x_unregister_notifier(struct device *dev, struct notifier_block *nb,
				unsigned int events)
{
	struct da903x_chip *chip = dev_get_drvdata(dev);

	chip->ops->mask_events(chip, events);
	return blocking_notifier_chain_unregister(&chip->notifier_list, nb);
}