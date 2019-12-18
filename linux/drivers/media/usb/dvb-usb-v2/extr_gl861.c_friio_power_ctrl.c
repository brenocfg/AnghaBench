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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int friio_reset (struct dvb_usb_device*) ; 

__attribute__((used)) static int friio_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	return onoff ? friio_reset(d) : 0;
}