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
struct rpisense {int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_client; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 

s32 rpisense_reg_read(struct rpisense *rpisense, int reg)
{
	int ret = i2c_smbus_read_byte_data(rpisense->i2c_client, reg);

	if (ret < 0)
		dev_err(rpisense->dev, "Read from reg %d failed\n", reg);
	/* Due to the BCM270x I2C clock stretching bug, some values
	 * may have MSB set. Clear it to avoid incorrect values.
	 * */
	return ret & 0x7F;
}