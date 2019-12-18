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
struct tps6105x {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TPS6105X_MODE_SHUTDOWN ; 
 int /*<<< orphan*/  TPS6105X_REG0_MODE_MASK ; 
 int TPS6105X_REG0_MODE_SHIFT ; 
 int /*<<< orphan*/  TPS6105X_REG_0 ; 
 struct tps6105x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tps6105x_remove(struct i2c_client *client)
{
	struct tps6105x *tps6105x = i2c_get_clientdata(client);

	mfd_remove_devices(&client->dev);

	/* Put chip in shutdown mode */
	regmap_update_bits(tps6105x->regmap, TPS6105X_REG_0,
		TPS6105X_REG0_MODE_MASK,
		TPS6105X_MODE_SHUTDOWN << TPS6105X_REG0_MODE_SHIFT);

	return 0;
}