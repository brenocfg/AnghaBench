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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct ec_params_i2c_passthru_msg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr_flags; } ;
struct ec_params_i2c_passthru {int num_msgs; struct ec_params_i2c_passthru_msg* msg; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_I2C_FLAG_READ ; 
 int EINVAL ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_i2c_construct_message(u8 *buf, const struct i2c_msg i2c_msgs[],
				    int num, u16 bus_num)
{
	struct ec_params_i2c_passthru *params;
	u8 *out_data;
	int i;

	out_data = buf + sizeof(struct ec_params_i2c_passthru) +
		   num * sizeof(struct ec_params_i2c_passthru_msg);

	params = (struct ec_params_i2c_passthru *)buf;
	params->port = bus_num;
	params->num_msgs = num;
	for (i = 0; i < num; i++) {
		const struct i2c_msg *i2c_msg = &i2c_msgs[i];
		struct ec_params_i2c_passthru_msg *msg = &params->msg[i];

		msg->len = i2c_msg->len;
		msg->addr_flags = i2c_msg->addr;

		if (i2c_msg->flags & I2C_M_TEN)
			return -EINVAL;

		if (i2c_msg->flags & I2C_M_RD) {
			msg->addr_flags |= EC_I2C_FLAG_READ;
		} else {
			memcpy(out_data, i2c_msg->buf, msg->len);
			out_data += msg->len;
		}
	}

	return 0;
}