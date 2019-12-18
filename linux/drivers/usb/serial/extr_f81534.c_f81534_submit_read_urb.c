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
struct usb_serial {int /*<<< orphan*/ * port; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int usb_serial_generic_submit_read_urbs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f81534_submit_read_urb(struct usb_serial *serial, gfp_t flags)
{
	return usb_serial_generic_submit_read_urbs(serial->port[0], flags);
}