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
struct max8997_dev {int /*<<< orphan*/  irq; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct max8997_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max8997_irq_resume (struct max8997_dev*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int max8997_resume(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	struct max8997_dev *max8997 = i2c_get_clientdata(i2c);

	if (device_may_wakeup(dev))
		irq_set_irq_wake(max8997->irq, 0);
	enable_irq(max8997->irq);
	return max8997_irq_resume(max8997);
}