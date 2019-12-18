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
typedef  unsigned char u32 ;
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  rspbuf ;
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 int pmbus_set_page (struct i2c_client*,int) ; 

__attribute__((used)) static int max31785_read_long_data(struct i2c_client *client, int page,
				   int reg, u32 *data)
{
	unsigned char cmdbuf[1];
	unsigned char rspbuf[4];
	int rc;

	struct i2c_msg msg[2] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = sizeof(cmdbuf),
			.buf = cmdbuf,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = sizeof(rspbuf),
			.buf = rspbuf,
		},
	};

	cmdbuf[0] = reg;

	rc = pmbus_set_page(client, page);
	if (rc < 0)
		return rc;

	rc = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	if (rc < 0)
		return rc;

	*data = (rspbuf[0] << (0 * 8)) | (rspbuf[1] << (1 * 8)) |
		(rspbuf[2] << (2 * 8)) | (rspbuf[3] << (3 * 8));

	return rc;
}