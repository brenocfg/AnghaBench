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
struct i2c_client {int /*<<< orphan*/  adapter; } ;
struct dw_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * slave; int /*<<< orphan*/  irq; int /*<<< orphan*/  (* disable ) (struct dw_i2c_dev*) ;int /*<<< orphan*/  (* disable_int ) (struct dw_i2c_dev*) ;} ;

/* Variables and functions */
 struct dw_i2c_dev* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  stub2 (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_dw_unreg_slave(struct i2c_client *slave)
{
	struct dw_i2c_dev *dev = i2c_get_adapdata(slave->adapter);

	dev->disable_int(dev);
	dev->disable(dev);
	synchronize_irq(dev->irq);
	dev->slave = NULL;
	pm_runtime_put(dev->dev);

	return 0;
}