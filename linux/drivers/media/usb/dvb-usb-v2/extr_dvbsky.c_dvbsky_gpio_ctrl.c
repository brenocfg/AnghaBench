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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int dvbsky_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int) ; 

__attribute__((used)) static int dvbsky_gpio_ctrl(struct dvb_usb_device *d, u8 gport, u8 value)
{
	int ret;
	u8 obuf[3], ibuf[2];

	obuf[0] = 0x0e;
	obuf[1] = gport;
	obuf[2] = value;
	ret = dvbsky_usb_generic_rw(d, obuf, 3, ibuf, 1);
	return ret;
}