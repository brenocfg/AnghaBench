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
struct usb_serial_port {int dummy; } ;
struct moschip_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct moschip_port*) ; 
 struct moschip_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int mos7720_port_remove(struct usb_serial_port *port)
{
	struct moschip_port *mos7720_port;

	mos7720_port = usb_get_serial_port_data(port);
	kfree(mos7720_port);

	return 0;
}