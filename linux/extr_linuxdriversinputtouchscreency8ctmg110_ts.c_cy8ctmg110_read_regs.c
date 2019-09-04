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
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct cy8ctmg110 {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int cy8ctmg110_read_regs(struct cy8ctmg110 *tsc,
		unsigned char *data, unsigned char len, unsigned char cmd)
{
	struct i2c_client *client = tsc->client;
	int ret;
	struct i2c_msg msg[2] = {
		/* first write slave position to i2c devices */
		{
			.addr = client->addr,
			.len = 1,
			.buf = &cmd
		},
		/* Second read data from position */
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = data
		}
	};

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
		return ret;

	return 0;
}