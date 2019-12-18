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
struct tca6416_keypad_chip {int /*<<< orphan*/  input; int /*<<< orphan*/  irqnum; int /*<<< orphan*/  use_polling; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tca6416_keypad_chip*) ; 
 struct tca6416_keypad_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tca6416_keypad_chip*) ; 

__attribute__((used)) static int tca6416_keypad_remove(struct i2c_client *client)
{
	struct tca6416_keypad_chip *chip = i2c_get_clientdata(client);

	if (!chip->use_polling) {
		free_irq(chip->irqnum, chip);
		enable_irq(chip->irqnum);
	}

	input_unregister_device(chip->input);
	kfree(chip);

	return 0;
}