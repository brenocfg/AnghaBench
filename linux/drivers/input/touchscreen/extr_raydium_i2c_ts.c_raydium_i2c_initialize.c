#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int main_ver; int sub_ver; int /*<<< orphan*/  hw_ver; } ;
struct raydium_data {scalar_t__ boot_mode; TYPE_1__ info; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ RAYDIUM_TS_BLDR ; 
 scalar_t__ RAYDIUM_TS_MAIN ; 
 int /*<<< orphan*/  RM_BOOT_DELAY_MS ; 
 int RM_MAX_RETRIES ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int raydium_i2c_check_fw_status (struct raydium_data*) ; 
 int /*<<< orphan*/  raydium_i2c_query_ts_info (struct raydium_data*) ; 

__attribute__((used)) static int raydium_i2c_initialize(struct raydium_data *ts)
{
	struct i2c_client *client = ts->client;
	int error, retry_cnt;

	for (retry_cnt = 0; retry_cnt < RM_MAX_RETRIES; retry_cnt++) {
		/* Wait for Hello packet */
		msleep(RM_BOOT_DELAY_MS);

		error = raydium_i2c_check_fw_status(ts);
		if (error) {
			dev_err(&client->dev,
				"failed to read 'hello' packet: %d\n", error);
			continue;
		}

		if (ts->boot_mode == RAYDIUM_TS_BLDR ||
		    ts->boot_mode == RAYDIUM_TS_MAIN) {
			break;
		}
	}

	if (error)
		ts->boot_mode = RAYDIUM_TS_BLDR;

	if (ts->boot_mode == RAYDIUM_TS_BLDR) {
		ts->info.hw_ver = cpu_to_le32(0xffffffffUL);
		ts->info.main_ver = 0xff;
		ts->info.sub_ver = 0xff;
	} else {
		raydium_i2c_query_ts_info(ts);
	}

	return error;
}