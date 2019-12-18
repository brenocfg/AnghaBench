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
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; struct af9005_device_state* priv; } ;
struct af9005_device_state {int* data; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int AF9005_CMD_AUTOINC ; 
 int AF9005_CMD_BURST ; 
 int AF9005_CMD_OFDM_REG ; 
 int AF9005_CMD_READ ; 
 int AF9005_CMD_TUNER ; 
 int AF9005_CMD_WRITE ; 
 int AF9005_OFDM_REG ; 
 int AF9005_REGISTER_RW ; 
 int AF9005_REGISTER_RW_ACK ; 
 int AF9005_TUNER_REG ; 
 int EINVAL ; 
 int EIO ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int af9005_generic_read_write(struct dvb_usb_device *d, u16 reg,
			      int readwrite, int type, u8 * values, int len)
{
	struct af9005_device_state *st = d->priv;
	u8 command, seq;
	int i, ret;

	if (len < 1) {
		err("generic read/write, less than 1 byte. Makes no sense.");
		return -EINVAL;
	}
	if (len > 8) {
		err("generic read/write, more than 8 bytes. Not supported.");
		return -EINVAL;
	}

	mutex_lock(&d->data_mutex);
	st->data[0] = 14;		/* rest of buffer length low */
	st->data[1] = 0;		/* rest of buffer length high */

	st->data[2] = AF9005_REGISTER_RW;	/* register operation */
	st->data[3] = 12;		/* rest of buffer length */

	st->data[4] = seq = st->sequence++;	/* sequence number */

	st->data[5] = (u8) (reg >> 8);	/* register address */
	st->data[6] = (u8) (reg & 0xff);

	if (type == AF9005_OFDM_REG) {
		command = AF9005_CMD_OFDM_REG;
	} else {
		command = AF9005_CMD_TUNER;
	}

	if (len > 1)
		command |=
		    AF9005_CMD_BURST | AF9005_CMD_AUTOINC | (len - 1) << 3;
	command |= readwrite;
	if (readwrite == AF9005_CMD_WRITE)
		for (i = 0; i < len; i++)
			st->data[8 + i] = values[i];
	else if (type == AF9005_TUNER_REG)
		/* read command for tuner, the first byte contains the i2c address */
		st->data[8] = values[0];
	st->data[7] = command;

	ret = dvb_usb_generic_rw(d, st->data, 16, st->data, 17, 0);
	if (ret)
		goto ret;

	/* sanity check */
	if (st->data[2] != AF9005_REGISTER_RW_ACK) {
		err("generic read/write, wrong reply code.");
		ret = -EIO;
		goto ret;
	}
	if (st->data[3] != 0x0d) {
		err("generic read/write, wrong length in reply.");
		ret = -EIO;
		goto ret;
	}
	if (st->data[4] != seq) {
		err("generic read/write, wrong sequence in reply.");
		ret = -EIO;
		goto ret;
	}
	/*
	 * In thesis, both input and output buffers should have
	 * identical values for st->data[5] to st->data[8].
	 * However, windows driver doesn't check these fields, in fact
	 * sometimes the register in the reply is different that what
	 * has been sent
	 */
	if (st->data[16] != 0x01) {
		err("generic read/write wrong status code in reply.");
		ret = -EIO;
		goto ret;
	}

	if (readwrite == AF9005_CMD_READ)
		for (i = 0; i < len; i++)
			values[i] = st->data[8 + i];

ret:
	mutex_unlock(&d->data_mutex);
	return ret;

}