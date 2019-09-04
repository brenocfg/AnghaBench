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
struct vprbrd_i2c_status {int dummy; } ;
struct vprbrd_i2c_addr_msg {int unknown2; int unknown3; int unknown1; void* len; int /*<<< orphan*/  addr; void* cmd; } ;
struct vprbrd {int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_dev; scalar_t__ buf; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; scalar_t__ algo_data; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 void* VPRBRD_I2C_CMD_ADDR ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vprbrd_i2c_addr (int /*<<< orphan*/ ,struct vprbrd_i2c_addr_msg*) ; 
 int vprbrd_i2c_read (struct vprbrd*,struct i2c_msg*) ; 
 int vprbrd_i2c_status (struct i2c_adapter*,struct vprbrd_i2c_status*,int) ; 
 int vprbrd_i2c_write (struct vprbrd*,struct i2c_msg*) ; 

__attribute__((used)) static int vprbrd_i2c_xfer(struct i2c_adapter *i2c, struct i2c_msg *msgs,
		int num)
{
	struct i2c_msg *pmsg;
	int i, ret,
		error = 0;
	struct vprbrd *vb = (struct vprbrd *)i2c->algo_data;
	struct vprbrd_i2c_addr_msg *amsg =
		(struct vprbrd_i2c_addr_msg *)vb->buf;
	struct vprbrd_i2c_status *smsg = (struct vprbrd_i2c_status *)vb->buf;

	dev_dbg(&i2c->dev, "master xfer %d messages:\n", num);

	for (i = 0 ; i < num ; i++) {
		pmsg = &msgs[i];

		dev_dbg(&i2c->dev,
			"  %d: %s (flags %d) %d bytes to 0x%02x\n",
			i, pmsg->flags & I2C_M_RD ? "read" : "write",
			pmsg->flags, pmsg->len, pmsg->addr);

		mutex_lock(&vb->lock);
		/* directly send the message */
		if (pmsg->flags & I2C_M_RD) {
			/* read data */
			amsg->cmd = VPRBRD_I2C_CMD_ADDR;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addr = pmsg->addr;
			amsg->unknown1 = 0x01;
			amsg->len = cpu_to_le16(pmsg->len);
			/* send the addr and len, we're interested to board */
			ret = vprbrd_i2c_addr(vb->usb_dev, amsg);
			if (ret < 0)
				error = ret;

			ret = vprbrd_i2c_read(vb, pmsg);
			if (ret < 0)
				error = ret;

			ret = vprbrd_i2c_status(i2c, smsg, error);
			if (ret < 0)
				error = ret;
			/* in case of protocol error, return the error */
			if (error < 0)
				goto error;
		} else {
			/* write data */
			ret = vprbrd_i2c_write(vb, pmsg);

			amsg->cmd = VPRBRD_I2C_CMD_ADDR;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addr = pmsg->addr;
			amsg->unknown1 = 0x00;
			amsg->len = cpu_to_le16(pmsg->len);
			/* send the addr, the data goes to to board */
			ret = vprbrd_i2c_addr(vb->usb_dev, amsg);
			if (ret < 0)
				error = ret;

			ret = vprbrd_i2c_status(i2c, smsg, error);
			if (ret < 0)
				error = ret;

			if (error < 0)
				goto error;
		}
		mutex_unlock(&vb->lock);
	}
	return num;
error:
	mutex_unlock(&vb->lock);
	return error;
}