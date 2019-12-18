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
struct max14577 {scalar_t__ dev_type; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAXIM_DEVICE_TYPE_MAX77836 ; 
 struct max14577* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  max77836_remove (struct max14577*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max14577_i2c_remove(struct i2c_client *i2c)
{
	struct max14577 *max14577 = i2c_get_clientdata(i2c);

	mfd_remove_devices(max14577->dev);
	regmap_del_irq_chip(max14577->irq, max14577->irq_data);
	if (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836)
		max77836_remove(max14577);

	return 0;
}