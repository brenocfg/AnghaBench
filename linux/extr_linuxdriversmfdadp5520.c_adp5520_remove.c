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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adp5520_chip {int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_MODE_STATUS ; 
 int /*<<< orphan*/  adp5520_remove_subdevs (struct adp5520_chip*) ; 
 int /*<<< orphan*/  adp5520_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adp5520_chip* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct adp5520_chip*) ; 

__attribute__((used)) static int adp5520_remove(struct i2c_client *client)
{
	struct adp5520_chip *chip = dev_get_drvdata(&client->dev);

	if (chip->irq)
		free_irq(chip->irq, chip);

	adp5520_remove_subdevs(chip);
	adp5520_write(chip->dev, ADP5520_MODE_STATUS, 0);
	return 0;
}