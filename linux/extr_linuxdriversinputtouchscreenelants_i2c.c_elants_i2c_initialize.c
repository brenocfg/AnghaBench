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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct elants_data {int /*<<< orphan*/  iap_mode; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  recov_packet ;
typedef  int /*<<< orphan*/  hello_packet ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_TIME_DELAY_MS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ELAN_IAP_OPERATIONAL ; 
 int /*<<< orphan*/  ELAN_IAP_RECOVERY ; 
 int HEADER_SIZE ; 
 int MAX_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int elants_i2c_fastboot (struct i2c_client*) ; 
 int elants_i2c_query_bc_version (struct elants_data*) ; 
 int elants_i2c_query_fw_version (struct elants_data*) ; 
 int elants_i2c_query_hw_version (struct elants_data*) ; 
 int elants_i2c_query_test_version (struct elants_data*) ; 
 int elants_i2c_query_ts_info (struct elants_data*) ; 
 int elants_i2c_read (struct i2c_client*,int*,int) ; 
 int elants_i2c_sw_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elants_i2c_initialize(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	int error, error2, retry_cnt;
	const u8 hello_packet[] = { 0x55, 0x55, 0x55, 0x55 };
	const u8 recov_packet[] = { 0x55, 0x55, 0x80, 0x80 };
	u8 buf[HEADER_SIZE];

	for (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) {
		error = elants_i2c_sw_reset(client);
		if (error) {
			/* Continue initializing if it's the last try */
			if (retry_cnt < MAX_RETRIES - 1)
				continue;
		}

		error = elants_i2c_fastboot(client);
		if (error) {
			/* Continue initializing if it's the last try */
			if (retry_cnt < MAX_RETRIES - 1)
				continue;
		}

		/* Wait for Hello packet */
		msleep(BOOT_TIME_DELAY_MS);

		error = elants_i2c_read(client, buf, sizeof(buf));
		if (error) {
			dev_err(&client->dev,
				"failed to read 'hello' packet: %d\n", error);
		} else if (!memcmp(buf, hello_packet, sizeof(hello_packet))) {
			ts->iap_mode = ELAN_IAP_OPERATIONAL;
			break;
		} else if (!memcmp(buf, recov_packet, sizeof(recov_packet))) {
			/*
			 * Setting error code will mark device
			 * in recovery mode below.
			 */
			error = -EIO;
			break;
		} else {
			error = -EINVAL;
			dev_err(&client->dev,
				"invalid 'hello' packet: %*ph\n",
				(int)sizeof(buf), buf);
		}
	}

	/* hw version is available even if device in recovery state */
	error2 = elants_i2c_query_hw_version(ts);
	if (!error)
		error = error2;

	if (!error)
		error = elants_i2c_query_fw_version(ts);
	if (!error)
		error = elants_i2c_query_test_version(ts);
	if (!error)
		error = elants_i2c_query_bc_version(ts);
	if (!error)
		error = elants_i2c_query_ts_info(ts);

	if (error)
		ts->iap_mode = ELAN_IAP_RECOVERY;

	return 0;
}