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
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct tca6416_keypad_chip* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void tca6416_keys_close(struct input_dev *dev)
{
	struct tca6416_keypad_chip *chip = input_get_drvdata(dev);

	if (chip->use_polling)
		cancel_delayed_work_sync(&chip->dwork);
	else
		disable_irq(chip->irqnum);
}