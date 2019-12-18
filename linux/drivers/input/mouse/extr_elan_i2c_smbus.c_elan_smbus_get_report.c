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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  ETP_SMBUS_PACKET_QUERY ; 
 int ETP_SMBUS_REPORT_LEN ; 
 size_t ETP_SMBUS_REPORT_OFFSET ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_smbus_get_report(struct i2c_client *client, u8 *report)
{
	int len;

	BUILD_BUG_ON(I2C_SMBUS_BLOCK_MAX > ETP_SMBUS_REPORT_LEN);

	len = i2c_smbus_read_block_data(client,
					ETP_SMBUS_PACKET_QUERY,
					&report[ETP_SMBUS_REPORT_OFFSET]);
	if (len < 0) {
		dev_err(&client->dev, "failed to read report data: %d\n", len);
		return len;
	}

	if (len != ETP_SMBUS_REPORT_LEN) {
		dev_err(&client->dev,
			"wrong report length (%d vs %d expected)\n",
			len, ETP_SMBUS_REPORT_LEN);
		return -EIO;
	}

	return 0;
}