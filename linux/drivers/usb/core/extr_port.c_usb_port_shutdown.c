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
struct usb_port {scalar_t__ child; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_port* to_usb_port (struct device*) ; 
 int /*<<< orphan*/  usb_disable_usb2_hardware_lpm (scalar_t__) ; 

__attribute__((used)) static void usb_port_shutdown(struct device *dev)
{
	struct usb_port *port_dev = to_usb_port(dev);

	if (port_dev->child)
		usb_disable_usb2_hardware_lpm(port_dev->child);
}