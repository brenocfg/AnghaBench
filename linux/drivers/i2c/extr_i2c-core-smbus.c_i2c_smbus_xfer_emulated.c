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
union i2c_smbus_data {unsigned char byte; int word; int* block; } ;
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {unsigned short flags; int len; unsigned char* buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 unsigned short I2C_CLIENT_PEC ; 
 int I2C_M_DMA_SAFE ; 
 unsigned short I2C_M_RD ; 
 unsigned short I2C_M_RECV_LEN ; 
#define  I2C_SMBUS_BLOCK_DATA 135 
 int I2C_SMBUS_BLOCK_MAX ; 
#define  I2C_SMBUS_BLOCK_PROC_CALL 134 
#define  I2C_SMBUS_BYTE 133 
#define  I2C_SMBUS_BYTE_DATA 132 
#define  I2C_SMBUS_I2C_BLOCK_DATA 131 
#define  I2C_SMBUS_PROC_CALL 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 int __i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  i2c_smbus_add_pec (struct i2c_msg*) ; 
 int i2c_smbus_check_pec (unsigned char,struct i2c_msg*) ; 
 unsigned char i2c_smbus_msg_pec (int /*<<< orphan*/ ,struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_smbus_try_get_dmabuf (struct i2c_msg*,unsigned char) ; 
 int /*<<< orphan*/  kfree (int*) ; 

__attribute__((used)) static s32 i2c_smbus_xfer_emulated(struct i2c_adapter *adapter, u16 addr,
				   unsigned short flags,
				   char read_write, u8 command, int size,
				   union i2c_smbus_data *data)
{
	/*
	 * So we need to generate a series of msgs. In the case of writing, we
	 * need to use only one message; when reading, we need two. We
	 * initialize most things with sane defaults, to keep the code below
	 * somewhat simpler.
	 */
	unsigned char msgbuf0[I2C_SMBUS_BLOCK_MAX+3];
	unsigned char msgbuf1[I2C_SMBUS_BLOCK_MAX+2];
	int num = read_write == I2C_SMBUS_READ ? 2 : 1;
	int i;
	u8 partial_pec = 0;
	int status;
	struct i2c_msg msg[2] = {
		{
			.addr = addr,
			.flags = flags,
			.len = 1,
			.buf = msgbuf0,
		}, {
			.addr = addr,
			.flags = flags | I2C_M_RD,
			.len = 0,
			.buf = msgbuf1,
		},
	};

	msgbuf0[0] = command;
	switch (size) {
	case I2C_SMBUS_QUICK:
		msg[0].len = 0;
		/* Special case: The read/write field is used as data */
		msg[0].flags = flags | (read_write == I2C_SMBUS_READ ?
					I2C_M_RD : 0);
		num = 1;
		break;
	case I2C_SMBUS_BYTE:
		if (read_write == I2C_SMBUS_READ) {
			/* Special case: only a read! */
			msg[0].flags = I2C_M_RD | flags;
			num = 1;
		}
		break;
	case I2C_SMBUS_BYTE_DATA:
		if (read_write == I2C_SMBUS_READ)
			msg[1].len = 1;
		else {
			msg[0].len = 2;
			msgbuf0[1] = data->byte;
		}
		break;
	case I2C_SMBUS_WORD_DATA:
		if (read_write == I2C_SMBUS_READ)
			msg[1].len = 2;
		else {
			msg[0].len = 3;
			msgbuf0[1] = data->word & 0xff;
			msgbuf0[2] = data->word >> 8;
		}
		break;
	case I2C_SMBUS_PROC_CALL:
		num = 2; /* Special case */
		read_write = I2C_SMBUS_READ;
		msg[0].len = 3;
		msg[1].len = 2;
		msgbuf0[1] = data->word & 0xff;
		msgbuf0[2] = data->word >> 8;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		if (read_write == I2C_SMBUS_READ) {
			msg[1].flags |= I2C_M_RECV_LEN;
			msg[1].len = 1; /* block length will be added by
					   the underlying bus driver */
			i2c_smbus_try_get_dmabuf(&msg[1], 0);
		} else {
			msg[0].len = data->block[0] + 2;
			if (msg[0].len > I2C_SMBUS_BLOCK_MAX + 2) {
				dev_err(&adapter->dev,
					"Invalid block write size %d\n",
					data->block[0]);
				return -EINVAL;
			}

			i2c_smbus_try_get_dmabuf(&msg[0], command);
			for (i = 1; i < msg[0].len; i++)
				msg[0].buf[i] = data->block[i - 1];
		}
		break;
	case I2C_SMBUS_BLOCK_PROC_CALL:
		num = 2; /* Another special case */
		read_write = I2C_SMBUS_READ;
		if (data->block[0] > I2C_SMBUS_BLOCK_MAX) {
			dev_err(&adapter->dev,
				"Invalid block write size %d\n",
				data->block[0]);
			return -EINVAL;
		}

		msg[0].len = data->block[0] + 2;
		i2c_smbus_try_get_dmabuf(&msg[0], command);
		for (i = 1; i < msg[0].len; i++)
			msg[0].buf[i] = data->block[i - 1];

		msg[1].flags |= I2C_M_RECV_LEN;
		msg[1].len = 1; /* block length will be added by
				   the underlying bus driver */
		i2c_smbus_try_get_dmabuf(&msg[1], 0);
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		if (data->block[0] > I2C_SMBUS_BLOCK_MAX) {
			dev_err(&adapter->dev, "Invalid block %s size %d\n",
				read_write == I2C_SMBUS_READ ? "read" : "write",
				data->block[0]);
			return -EINVAL;
		}

		if (read_write == I2C_SMBUS_READ) {
			msg[1].len = data->block[0];
			i2c_smbus_try_get_dmabuf(&msg[1], 0);
		} else {
			msg[0].len = data->block[0] + 1;

			i2c_smbus_try_get_dmabuf(&msg[0], command);
			for (i = 1; i <= data->block[0]; i++)
				msg[0].buf[i] = data->block[i];
		}
		break;
	default:
		dev_err(&adapter->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	i = ((flags & I2C_CLIENT_PEC) && size != I2C_SMBUS_QUICK
				      && size != I2C_SMBUS_I2C_BLOCK_DATA);
	if (i) {
		/* Compute PEC if first message is a write */
		if (!(msg[0].flags & I2C_M_RD)) {
			if (num == 1) /* Write only */
				i2c_smbus_add_pec(&msg[0]);
			else /* Write followed by read */
				partial_pec = i2c_smbus_msg_pec(0, &msg[0]);
		}
		/* Ask for PEC if last message is a read */
		if (msg[num-1].flags & I2C_M_RD)
			msg[num-1].len++;
	}

	status = __i2c_transfer(adapter, msg, num);
	if (status < 0)
		goto cleanup;
	if (status != num) {
		status = -EIO;
		goto cleanup;
	}
	status = 0;

	/* Check PEC if last message is a read */
	if (i && (msg[num-1].flags & I2C_M_RD)) {
		status = i2c_smbus_check_pec(partial_pec, &msg[num-1]);
		if (status < 0)
			goto cleanup;
	}

	if (read_write == I2C_SMBUS_READ)
		switch (size) {
		case I2C_SMBUS_BYTE:
			data->byte = msgbuf0[0];
			break;
		case I2C_SMBUS_BYTE_DATA:
			data->byte = msgbuf1[0];
			break;
		case I2C_SMBUS_WORD_DATA:
		case I2C_SMBUS_PROC_CALL:
			data->word = msgbuf1[0] | (msgbuf1[1] << 8);
			break;
		case I2C_SMBUS_I2C_BLOCK_DATA:
			for (i = 0; i < data->block[0]; i++)
				data->block[i + 1] = msg[1].buf[i];
			break;
		case I2C_SMBUS_BLOCK_DATA:
		case I2C_SMBUS_BLOCK_PROC_CALL:
			for (i = 0; i < msg[1].buf[0] + 1; i++)
				data->block[i] = msg[1].buf[i];
			break;
		}

cleanup:
	if (msg[0].flags & I2C_M_DMA_SAFE)
		kfree(msg[0].buf);
	if (msg[1].flags & I2C_M_DMA_SAFE)
		kfree(msg[1].buf);

	return status;
}