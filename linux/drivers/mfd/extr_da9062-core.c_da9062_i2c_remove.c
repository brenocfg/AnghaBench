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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct da9062 {int /*<<< orphan*/  regmap_irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct da9062* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9062_i2c_remove(struct i2c_client *i2c)
{
	struct da9062 *chip = i2c_get_clientdata(i2c);

	mfd_remove_devices(chip->dev);
	regmap_del_irq_chip(i2c->irq, chip->regmap_irq);

	return 0;
}