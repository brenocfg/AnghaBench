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
struct mcs_platform_data {int x_size; int y_size; } ;
struct mcs5000_ts_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCS5000_TS_OP_MODE ; 
 int /*<<< orphan*/  MCS5000_TS_X_SIZE_LOWER ; 
 int /*<<< orphan*/  MCS5000_TS_X_SIZE_UPPER ; 
 int /*<<< orphan*/  MCS5000_TS_Y_SIZE_LOWER ; 
 int /*<<< orphan*/  MCS5000_TS_Y_SIZE_UPPER ; 
 int OP_MODE_ACTIVE ; 
 int OP_MODE_SLEEP ; 
 int REPORT_RATE_80 ; 
 int RESET_EXT_SOFT ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcs5000_ts_phys_init(struct mcs5000_ts_data *data,
				 const struct mcs_platform_data *platform_data)
{
	struct i2c_client *client = data->client;

	/* Touch reset & sleep mode */
	i2c_smbus_write_byte_data(client, MCS5000_TS_OP_MODE,
			RESET_EXT_SOFT | OP_MODE_SLEEP);

	/* Touch size */
	i2c_smbus_write_byte_data(client, MCS5000_TS_X_SIZE_UPPER,
			platform_data->x_size >> 8);
	i2c_smbus_write_byte_data(client, MCS5000_TS_X_SIZE_LOWER,
			platform_data->x_size & 0xff);
	i2c_smbus_write_byte_data(client, MCS5000_TS_Y_SIZE_UPPER,
			platform_data->y_size >> 8);
	i2c_smbus_write_byte_data(client, MCS5000_TS_Y_SIZE_LOWER,
			platform_data->y_size & 0xff);

	/* Touch active mode & 80 report rate */
	i2c_smbus_write_byte_data(data->client, MCS5000_TS_OP_MODE,
			OP_MODE_ACTIVE | REPORT_RATE_80);
}