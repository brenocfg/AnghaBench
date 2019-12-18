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
struct max77693_dev {int /*<<< orphan*/  i2c_haptic; int /*<<< orphan*/  i2c_muic; int /*<<< orphan*/  irq_data_led; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_data_topsys; int /*<<< orphan*/  irq_data_chg; int /*<<< orphan*/  irq_data_muic; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct max77693_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77693_i2c_remove(struct i2c_client *i2c)
{
	struct max77693_dev *max77693 = i2c_get_clientdata(i2c);

	mfd_remove_devices(max77693->dev);

	regmap_del_irq_chip(max77693->irq, max77693->irq_data_muic);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_chg);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_topsys);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_led);

	i2c_unregister_device(max77693->i2c_muic);
	i2c_unregister_device(max77693->i2c_haptic);

	return 0;
}