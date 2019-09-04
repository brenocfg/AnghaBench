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
struct pm860x_chip {scalar_t__ companion; int /*<<< orphan*/  regmap_companion; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct pm860x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  pm860x_device_exit (struct pm860x_chip*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_remove(struct i2c_client *client)
{
	struct pm860x_chip *chip = i2c_get_clientdata(client);

	pm860x_device_exit(chip);
	if (chip->companion) {
		regmap_exit(chip->regmap_companion);
		i2c_unregister_device(chip->companion);
	}
	return 0;
}