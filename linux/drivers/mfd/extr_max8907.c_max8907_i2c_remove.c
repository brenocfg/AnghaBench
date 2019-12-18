#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct max8907 {int /*<<< orphan*/  i2c_rtc; int /*<<< orphan*/  irqc_chg; TYPE_1__* i2c_gen; int /*<<< orphan*/  irqc_on_off; int /*<<< orphan*/  irqc_rtc; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct max8907* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8907_i2c_remove(struct i2c_client *i2c)
{
	struct max8907 *max8907 = i2c_get_clientdata(i2c);

	mfd_remove_devices(max8907->dev);

	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_rtc);
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_on_off);
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_chg);

	i2c_unregister_device(max8907->i2c_rtc);

	return 0;
}