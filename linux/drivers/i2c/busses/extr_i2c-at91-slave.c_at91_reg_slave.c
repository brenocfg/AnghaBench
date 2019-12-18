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
struct i2c_client {int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;
struct at91_twi_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  smr; struct i2c_client* slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_IER ; 
 int /*<<< orphan*/  AT91_TWI_SMR_SADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_TWI_SVACC ; 
 int EAFNOSUPPORT ; 
 int EBUSY ; 
 int I2C_CLIENT_TEN ; 
 int /*<<< orphan*/  at91_init_twi_bus (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct at91_twi_dev* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_reg_slave(struct i2c_client *slave)
{
	struct at91_twi_dev *dev = i2c_get_adapdata(slave->adapter);

	if (dev->slave)
		return -EBUSY;

	if (slave->flags & I2C_CLIENT_TEN)
		return -EAFNOSUPPORT;

	/* Make sure twi_clk doesn't get turned off! */
	pm_runtime_get_sync(dev->dev);

	dev->slave = slave;
	dev->smr = AT91_TWI_SMR_SADR(slave->addr);

	at91_init_twi_bus(dev);
	at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_SVACC);

	dev_info(dev->dev, "entered slave mode (ADR=%d)\n", slave->addr);

	return 0;
}