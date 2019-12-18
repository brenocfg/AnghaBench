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
struct dvb_usb_device {int /*<<< orphan*/  udev; struct dtv5100_state* priv; } ;
struct dtv5100_state {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int DTV5100_DEMOD_ADDR ; 
 int DTV5100_DEMOD_READ ; 
 int DTV5100_DEMOD_WRITE ; 
 int DTV5100_TUNER_READ ; 
 int DTV5100_TUNER_WRITE ; 
 int /*<<< orphan*/  DTV5100_USB_TIMEOUT ; 
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int dtv5100_i2c_msg(struct dvb_usb_device *d, u8 addr,
			   u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	struct dtv5100_state *st = d->priv;
	u8 request;
	u8 type;
	u16 value;
	u16 index;

	switch (wlen) {
	case 1:
		/* write { reg }, read { value } */
		request = (addr == DTV5100_DEMOD_ADDR ? DTV5100_DEMOD_READ :
							DTV5100_TUNER_READ);
		type = USB_TYPE_VENDOR | USB_DIR_IN;
		value = 0;
		break;
	case 2:
		/* write { reg, value } */
		request = (addr == DTV5100_DEMOD_ADDR ? DTV5100_DEMOD_WRITE :
							DTV5100_TUNER_WRITE);
		type = USB_TYPE_VENDOR | USB_DIR_OUT;
		value = wbuf[1];
		break;
	default:
		warn("wlen = %x, aborting.", wlen);
		return -EINVAL;
	}
	index = (addr << 8) + wbuf[0];

	memcpy(st->data, rbuf, rlen);
	msleep(1); /* avoid I2C errors */
	return usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), request,
			       type, value, index, st->data, rlen,
			       DTV5100_USB_TIMEOUT);
}