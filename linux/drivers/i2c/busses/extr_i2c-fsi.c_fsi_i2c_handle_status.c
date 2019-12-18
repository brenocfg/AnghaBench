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
typedef  int u32 ;
struct i2c_msg {int flags; scalar_t__ len; } ;
struct fsi_i2c_port {scalar_t__ xfrd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EIO ; 
 int ENODATA ; 
 int ENXIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int I2C_M_RD ; 
 int I2C_STAT_BE_ACCESS ; 
 int I2C_STAT_BE_OVERRUN ; 
 int I2C_STAT_CMD_COMP ; 
 int I2C_STAT_DAT_REQ ; 
 int I2C_STAT_ERR ; 
 int /*<<< orphan*/  I2C_STAT_FIFO_COUNT ; 
 int I2C_STAT_INV_CMD ; 
 int I2C_STAT_LOST_ARB ; 
 int I2C_STAT_NACK ; 
 int I2C_STAT_PARITY ; 
 int I2C_STAT_STOP_ERR ; 
 int fsi_i2c_abort (struct fsi_i2c_port*,int) ; 
 int fsi_i2c_read_fifo (struct fsi_i2c_port*,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 int fsi_i2c_write_fifo (struct fsi_i2c_port*,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_i2c_handle_status(struct fsi_i2c_port *port,
				 struct i2c_msg *msg, u32 status)
{
	int rc;
	u8 fifo_count;

	if (status & I2C_STAT_ERR) {
		rc = fsi_i2c_abort(port, status);
		if (rc)
			return rc;

		if (status & I2C_STAT_INV_CMD)
			return -EINVAL;

		if (status & (I2C_STAT_PARITY | I2C_STAT_BE_OVERRUN |
		    I2C_STAT_BE_ACCESS))
			return -EPROTO;

		if (status & I2C_STAT_NACK)
			return -ENXIO;

		if (status & I2C_STAT_LOST_ARB)
			return -EAGAIN;

		if (status & I2C_STAT_STOP_ERR)
			return -EBADMSG;

		return -EIO;
	}

	if (status & I2C_STAT_DAT_REQ) {
		fifo_count = FIELD_GET(I2C_STAT_FIFO_COUNT, status);

		if (msg->flags & I2C_M_RD)
			return fsi_i2c_read_fifo(port, msg, fifo_count);

		return fsi_i2c_write_fifo(port, msg, fifo_count);
	}

	if (status & I2C_STAT_CMD_COMP) {
		if (port->xfrd < msg->len)
			return -ENODATA;

		return msg->len;
	}

	return 0;
}