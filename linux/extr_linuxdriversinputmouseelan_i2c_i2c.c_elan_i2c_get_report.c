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
 int EIO ; 
 int ETP_I2C_REPORT_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int elan_i2c_get_report(struct i2c_client *client, u8 *report)
{
	int len;

	len = i2c_master_recv(client, report, ETP_I2C_REPORT_LEN);
	if (len < 0) {
		dev_err(&client->dev, "failed to read report data: %d\n", len);
		return len;
	}

	if (len != ETP_I2C_REPORT_LEN) {
		dev_err(&client->dev,
			"wrong report length (%d vs %d expected)\n",
			len, ETP_I2C_REPORT_LEN);
		return -EIO;
	}

	return 0;
}