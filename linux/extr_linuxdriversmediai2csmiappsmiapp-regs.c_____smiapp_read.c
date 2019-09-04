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
typedef  unsigned char u8 ;
typedef  unsigned char u32 ;
typedef  int u16 ;
struct smiapp_sensor {TYPE_1__* src; } ;
struct i2c_msg {int len; unsigned char* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
 scalar_t__ I2C_M_RD ; 
#define  SMIAPP_REG_16BIT 130 
#define  SMIAPP_REG_32BIT 129 
#define  SMIAPP_REG_8BIT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ____smiapp_read(struct smiapp_sensor *sensor, u16 reg,
			   u16 len, u32 *val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	struct i2c_msg msg;
	unsigned char data[4];
	u16 offset = reg;
	int r;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = data;

	/* high byte goes out first */
	data[0] = (u8) (offset >> 8);
	data[1] = (u8) offset;
	r = i2c_transfer(client->adapter, &msg, 1);
	if (r != 1) {
		if (r >= 0)
			r = -EBUSY;
		goto err;
	}

	msg.len = len;
	msg.flags = I2C_M_RD;
	r = i2c_transfer(client->adapter, &msg, 1);
	if (r != 1) {
		if (r >= 0)
			r = -EBUSY;
		goto err;
	}

	*val = 0;
	/* high byte comes first */
	switch (len) {
	case SMIAPP_REG_32BIT:
		*val = (data[0] << 24) + (data[1] << 16) + (data[2] << 8) +
			data[3];
		break;
	case SMIAPP_REG_16BIT:
		*val = (data[0] << 8) + data[1];
		break;
	case SMIAPP_REG_8BIT:
		*val = data[0];
		break;
	default:
		BUG();
	}

	return 0;

err:
	dev_err(&client->dev, "read from offset 0x%x error %d\n", offset, r);

	return r;
}