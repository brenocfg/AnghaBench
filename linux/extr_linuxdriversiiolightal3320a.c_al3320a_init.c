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
struct al3320a_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int AL3320A_CONFIG_ENABLE ; 
 int AL3320A_DEFAULT_MEAN_TIME ; 
 int AL3320A_DEFAULT_WAIT_TIME ; 
 int AL3320A_GAIN_SHIFT ; 
 int AL3320A_RANGE_3 ; 
 int /*<<< orphan*/  AL3320A_REG_CONFIG ; 
 int /*<<< orphan*/  AL3320A_REG_CONFIG_RANGE ; 
 int /*<<< orphan*/  AL3320A_REG_MEAN_TIME ; 
 int /*<<< orphan*/  AL3320A_REG_WAIT ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int al3320a_init(struct al3320a_data *data)
{
	int ret;

	/* power on */
	ret = i2c_smbus_write_byte_data(data->client, AL3320A_REG_CONFIG,
					AL3320A_CONFIG_ENABLE);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client, AL3320A_REG_CONFIG_RANGE,
					AL3320A_RANGE_3 << AL3320A_GAIN_SHIFT);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client, AL3320A_REG_MEAN_TIME,
					AL3320A_DEFAULT_MEAN_TIME);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client, AL3320A_REG_WAIT,
					AL3320A_DEFAULT_WAIT_TIME);
	if (ret < 0)
		return ret;

	return 0;
}