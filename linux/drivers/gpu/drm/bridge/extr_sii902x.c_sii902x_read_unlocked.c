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
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int __i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 

__attribute__((used)) static int sii902x_read_unlocked(struct i2c_client *i2c, u8 reg, u8 *val)
{
	union i2c_smbus_data data;
	int ret;

	ret = __i2c_smbus_xfer(i2c->adapter, i2c->addr, i2c->flags,
			       I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data);

	if (ret < 0)
		return ret;

	*val = data.byte;
	return 0;
}