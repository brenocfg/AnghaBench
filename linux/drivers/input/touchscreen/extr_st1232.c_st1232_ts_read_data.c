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
typedef  int u8 ;
struct st1232_ts_finger {int is_valid; int x; int y; int t; } ;
struct st1232_ts_data {int* read_buf; int read_buf_len; TYPE_1__* chip_info; struct i2c_client* client; struct st1232_ts_finger* finger; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int start_reg; int max_fingers; scalar_t__ have_z; } ;

/* Variables and functions */
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int st1232_ts_read_data(struct st1232_ts_data *ts)
{
	struct st1232_ts_finger *finger = ts->finger;
	struct i2c_client *client = ts->client;
	struct i2c_msg msg[2];
	int error;
	int i, y;
	u8 start_reg = ts->chip_info->start_reg;
	u8 *buf = ts->read_buf;

	/* read touchscreen data */
	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &start_reg;

	msg[1].addr = ts->client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = ts->read_buf_len;
	msg[1].buf = buf;

	error = i2c_transfer(client->adapter, msg, 2);
	if (error < 0)
		return error;

	for (i = 0, y = 0; i < ts->chip_info->max_fingers; i++, y += 3) {
		finger[i].is_valid = buf[i + y] >> 7;
		if (finger[i].is_valid) {
			finger[i].x = ((buf[i + y] & 0x0070) << 4) |
					buf[i + y + 1];
			finger[i].y = ((buf[i + y] & 0x0007) << 8) |
					buf[i + y + 2];

			/* st1232 includes a z-axis / touch strength */
			if (ts->chip_info->have_z)
				finger[i].t = buf[i + 6];
		}
	}

	return 0;
}