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
struct TYPE_2__ {int (* power_ctrl ) (struct dvb_usb_device*,int) ;} ;
struct dvb_usb_device {int powered; TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_info (char*,int) ; 
 int stub1 (struct dvb_usb_device*,int) ; 

int dvb_usb_device_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	if (onoff)
		d->powered++;
	else
		d->powered--;

	if (d->powered == 0 || (onoff && d->powered == 1)) { /* when switching from 1 to 0 or from 0 to 1 */
		deb_info("power control: %d\n", onoff);
		if (d->props.power_ctrl)
			return d->props.power_ctrl(d, onoff);
	}
	return 0;
}