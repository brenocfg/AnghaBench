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
 int gp8psk_bcm4500_reload (struct dvb_usb_device*) ; 

__attribute__((used)) static int gp8psk_fe_reload(void *priv)
{
	struct dvb_usb_device *d = priv;

	return gp8psk_bcm4500_reload(d);
}