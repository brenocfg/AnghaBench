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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int AU6610_REQ_I2C_READ ; 
 int AU6610_REQ_I2C_WRITE ; 
 int au6610_usb_msg (struct dvb_usb_device*,int,int,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au6610_i2c_msg(struct dvb_usb_device *d, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	u8 request;
	u8 wo = (rbuf == NULL || rlen == 0); /* write-only */

	if (wo) {
		request = AU6610_REQ_I2C_WRITE;
	} else { /* rw */
		request = AU6610_REQ_I2C_READ;
	}

	return au6610_usb_msg(d, request, addr, wbuf, wlen, rbuf, rlen);
}