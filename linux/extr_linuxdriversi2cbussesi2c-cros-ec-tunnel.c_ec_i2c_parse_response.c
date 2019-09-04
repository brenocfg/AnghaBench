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
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct ec_response_i2c_passthru {int i2c_status; int num_msgs; } ;

/* Variables and functions */
 int EC_I2C_STATUS_ERROR ; 
 int EC_I2C_STATUS_NAK ; 
 int EC_I2C_STATUS_TIMEOUT ; 
 int EIO ; 
 int ENXIO ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_i2c_parse_response(const u8 *buf, struct i2c_msg i2c_msgs[],
				 int *num)
{
	const struct ec_response_i2c_passthru *resp;
	const u8 *in_data;
	int i;

	in_data = buf + sizeof(struct ec_response_i2c_passthru);

	resp = (const struct ec_response_i2c_passthru *)buf;
	if (resp->i2c_status & EC_I2C_STATUS_TIMEOUT)
		return -ETIMEDOUT;
	else if (resp->i2c_status & EC_I2C_STATUS_NAK)
		return -ENXIO;
	else if (resp->i2c_status & EC_I2C_STATUS_ERROR)
		return -EIO;

	/* Other side could send us back fewer messages, but not more */
	if (resp->num_msgs > *num)
		return -EPROTO;
	*num = resp->num_msgs;

	for (i = 0; i < *num; i++) {
		struct i2c_msg *i2c_msg = &i2c_msgs[i];

		if (i2c_msgs[i].flags & I2C_M_RD) {
			memcpy(i2c_msg->buf, in_data, i2c_msg->len);
			in_data += i2c_msg->len;
		}
	}

	return 0;
}