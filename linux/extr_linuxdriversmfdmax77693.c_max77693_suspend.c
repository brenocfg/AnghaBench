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
struct max77693_dev {int /*<<< orphan*/  irq; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 struct max77693_dev* i2c_get_clientdata (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int max77693_suspend(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	struct max77693_dev *max77693 = i2c_get_clientdata(i2c);

	if (device_may_wakeup(dev)) {
		enable_irq_wake(max77693->irq);
		disable_irq(max77693->irq);
	}

	return 0;
}