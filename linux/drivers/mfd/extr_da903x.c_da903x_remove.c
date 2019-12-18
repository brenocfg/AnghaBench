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
struct i2c_client {int dummy; } ;
struct da903x_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da903x_remove_subdevs (struct da903x_chip*) ; 
 struct da903x_chip* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int da903x_remove(struct i2c_client *client)
{
	struct da903x_chip *chip = i2c_get_clientdata(client);

	da903x_remove_subdevs(chip);
	return 0;
}