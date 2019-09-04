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
typedef  void* u8 ;
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; struct af9005_device_state* priv; } ;
struct af9005_device_state {int* data; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int af9005_send_command(struct dvb_usb_device *d, u8 command, u8 * wbuf,
			int wlen, u8 * rbuf, int rlen)
{
	struct af9005_device_state *st = d->priv;

	int ret, i, packet_len;
	u8 seq;

	if (wlen < 0) {
		err("send command, wlen less than 0 bytes. Makes no sense.");
		return -EINVAL;
	}
	if (wlen > 54) {
		err("send command, wlen more than 54 bytes. Not supported.");
		return -EINVAL;
	}
	if (rlen > 54) {
		err("send command, rlen more than 54 bytes. Not supported.");
		return -EINVAL;
	}
	packet_len = wlen + 5;

	mutex_lock(&d->data_mutex);

	st->data[0] = (u8) (packet_len & 0xff);
	st->data[1] = (u8) ((packet_len & 0xff00) >> 8);

	st->data[2] = 0x26;		/* packet type */
	st->data[3] = wlen + 3;
	st->data[4] = seq = st->sequence++;
	st->data[5] = command;
	st->data[6] = wlen;
	for (i = 0; i < wlen; i++)
		st->data[7 + i] = wbuf[i];
	ret = dvb_usb_generic_rw(d, st->data, wlen + 7, st->data, rlen + 7, 0);
	if (st->data[2] != 0x27) {
		err("send command, wrong reply code.");
		ret = -EIO;
	} else if (st->data[4] != seq) {
		err("send command, wrong sequence in reply.");
		ret = -EIO;
	} else if (st->data[5] != 0x01) {
		err("send command, wrong status code in reply.");
		ret = -EIO;
	} else if (st->data[6] != rlen) {
		err("send command, invalid data length in reply.");
		ret = -EIO;
	}
	if (!ret) {
		for (i = 0; i < rlen; i++)
			rbuf[i] = st->data[i + 7];
	}

	mutex_unlock(&d->data_mutex);
	return ret;
}