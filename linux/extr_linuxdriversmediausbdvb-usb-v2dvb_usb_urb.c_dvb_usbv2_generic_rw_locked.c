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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int dvb_usb_v2_generic_io (struct dvb_usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dvb_usbv2_generic_rw_locked(struct dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	return dvb_usb_v2_generic_io(d, wbuf, wlen, rbuf, rlen);
}