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
typedef  int /*<<< orphan*/  u8 ;
struct bu21013_ts {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BU21013_SENSORS_BTN_0_7_REG ; 
 int EINVAL ; 
 int I2C_RETRY_COUNT ; 
 int LENGTH_OF_BUFFER ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bu21013_read_block_data(struct bu21013_ts *ts, u8 *buf)
{
	int ret, i;

	for (i = 0; i < I2C_RETRY_COUNT; i++) {
		ret = i2c_smbus_read_i2c_block_data(ts->client,
						    BU21013_SENSORS_BTN_0_7_REG,
						    LENGTH_OF_BUFFER, buf);
		if (ret == LENGTH_OF_BUFFER)
			return 0;
	}

	return -EINVAL;
}