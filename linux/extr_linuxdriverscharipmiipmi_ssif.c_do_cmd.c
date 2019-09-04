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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SSIF_IPMI_REQUEST ; 
 int /*<<< orphan*/  SSIF_IPMI_RESPONSE ; 
 int /*<<< orphan*/  SSIF_MSG_MSEC ; 
 int SSIF_RECV_RETRIES ; 
 int SSIF_SEND_RETRIES ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned char*) ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_cmd(struct i2c_client *client, int len, unsigned char *msg,
		  int *resp_len, unsigned char *resp)
{
	int retry_cnt;
	int ret;

	retry_cnt = SSIF_SEND_RETRIES;
 retry1:
	ret = i2c_smbus_write_block_data(client, SSIF_IPMI_REQUEST, len, msg);
	if (ret) {
		retry_cnt--;
		if (retry_cnt > 0)
			goto retry1;
		return -ENODEV;
	}

	ret = -ENODEV;
	retry_cnt = SSIF_RECV_RETRIES;
	while (retry_cnt > 0) {
		ret = i2c_smbus_read_block_data(client, SSIF_IPMI_RESPONSE,
						resp);
		if (ret > 0)
			break;
		msleep(SSIF_MSG_MSEC);
		retry_cnt--;
		if (retry_cnt <= 0)
			break;
	}

	if (ret > 0) {
		/* Validate that the response is correct. */
		if (ret < 3 ||
		    (resp[0] != (msg[0] | (1 << 2))) ||
		    (resp[1] != msg[1]))
			ret = -EINVAL;
		else {
			*resp_len = ret;
			ret = 0;
		}
	}

	return ret;
}