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
struct twl6040 {int /*<<< orphan*/  supplies; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; scalar_t__ power_count; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6040_NUM_SUPPLIES ; 
 struct twl6040* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_power (struct twl6040*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040_remove(struct i2c_client *client)
{
	struct twl6040 *twl6040 = i2c_get_clientdata(client);

	if (twl6040->power_count)
		twl6040_power(twl6040, 0);

	regmap_del_irq_chip(twl6040->irq, twl6040->irq_data);

	mfd_remove_devices(&client->dev);

	regulator_bulk_disable(TWL6040_NUM_SUPPLIES, twl6040->supplies);

	return 0;
}