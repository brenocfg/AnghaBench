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
struct at91_twi_dev {int /*<<< orphan*/  dev; scalar_t__ smr; int /*<<< orphan*/ * slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  at91_init_twi_bus (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct at91_twi_dev* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_unreg_slave(struct i2c_client *slave)
{
	struct at91_twi_dev *dev = i2c_get_adapdata(slave->adapter);

	WARN_ON(!dev->slave);

	dev_info(dev->dev, "leaving slave mode\n");

	dev->slave = NULL;
	dev->smr = 0;

	at91_init_twi_bus(dev);

	pm_runtime_put(dev->dev);

	return 0;
}