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
struct tca6416_keypad_chip {int /*<<< orphan*/  irqnum; int /*<<< orphan*/  dwork; scalar_t__ use_polling; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct tca6416_keypad_chip* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tca6416_keys_scan (struct tca6416_keypad_chip*) ; 

__attribute__((used)) static int tca6416_keys_open(struct input_dev *dev)
{
	struct tca6416_keypad_chip *chip = input_get_drvdata(dev);

	/* Get initial device state in case it has switches */
	tca6416_keys_scan(chip);

	if (chip->use_polling)
		schedule_delayed_work(&chip->dwork, msecs_to_jiffies(100));
	else
		enable_irq(chip->irqnum);

	return 0;
}