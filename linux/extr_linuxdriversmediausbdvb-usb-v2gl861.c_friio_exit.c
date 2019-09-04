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
 int /*<<< orphan*/  FRIIO_LED_STOPPED ; 
 int /*<<< orphan*/  friio_ext_ctl (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void friio_exit(struct dvb_usb_device *d)
{
	friio_ext_ctl(d, FRIIO_LED_STOPPED, false);
}