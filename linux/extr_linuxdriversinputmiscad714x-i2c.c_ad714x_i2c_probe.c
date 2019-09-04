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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ad714x_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 scalar_t__ IS_ERR (struct ad714x_chip*) ; 
 int PTR_ERR (struct ad714x_chip*) ; 
 int /*<<< orphan*/  ad714x_i2c_read ; 
 int /*<<< orphan*/  ad714x_i2c_write ; 
 struct ad714x_chip* ad714x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ad714x_chip*) ; 

__attribute__((used)) static int ad714x_i2c_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct ad714x_chip *chip;

	chip = ad714x_probe(&client->dev, BUS_I2C, client->irq,
			    ad714x_i2c_read, ad714x_i2c_write);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	i2c_set_clientdata(client, chip);

	return 0;
}