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
struct lm95234_data {int* tcrit1; int* tcrit2; int* toffset; int thyst; int sensor_type; int /*<<< orphan*/  interval; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  LM95234_REG_CONVRATE ; 
 int /*<<< orphan*/  LM95234_REG_OFFSET (int) ; 
 int /*<<< orphan*/  LM95234_REG_REM_MODEL ; 
 int /*<<< orphan*/  LM95234_REG_TCRIT1 (int) ; 
 int /*<<< orphan*/  LM95234_REG_TCRIT2 (int) ; 
 int /*<<< orphan*/  LM95234_REG_TCRIT_HYST ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * update_intervals ; 

__attribute__((used)) static int lm95234_fill_cache(struct lm95234_data *data,
			      struct i2c_client *client)
{
	int i, ret;

	ret = i2c_smbus_read_byte_data(client, LM95234_REG_CONVRATE);
	if (ret < 0)
		return ret;

	data->interval = msecs_to_jiffies(update_intervals[ret & 0x03]);

	for (i = 0; i < ARRAY_SIZE(data->tcrit1); i++) {
		ret = i2c_smbus_read_byte_data(client, LM95234_REG_TCRIT1(i));
		if (ret < 0)
			return ret;
		data->tcrit1[i] = ret;
	}
	for (i = 0; i < ARRAY_SIZE(data->tcrit2); i++) {
		ret = i2c_smbus_read_byte_data(client, LM95234_REG_TCRIT2(i));
		if (ret < 0)
			return ret;
		data->tcrit2[i] = ret;
	}
	for (i = 0; i < ARRAY_SIZE(data->toffset); i++) {
		ret = i2c_smbus_read_byte_data(client, LM95234_REG_OFFSET(i));
		if (ret < 0)
			return ret;
		data->toffset[i] = ret;
	}

	ret = i2c_smbus_read_byte_data(client, LM95234_REG_TCRIT_HYST);
	if (ret < 0)
		return ret;
	data->thyst = ret;

	ret = i2c_smbus_read_byte_data(client, LM95234_REG_REM_MODEL);
	if (ret < 0)
		return ret;
	data->sensor_type = ret;

	return 0;
}