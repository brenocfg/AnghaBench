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
struct da9150 {int /*<<< orphan*/  core_qif; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_irq_data; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct da9150* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_remove(struct i2c_client *client)
{
	struct da9150 *da9150 = i2c_get_clientdata(client);

	regmap_del_irq_chip(da9150->irq, da9150->regmap_irq_data);
	mfd_remove_devices(da9150->dev);
	i2c_unregister_device(da9150->core_qif);

	return 0;
}