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
struct ftdi_private {int flags; int latency; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ASYNC_LOW_LATENCY ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct usb_serial_port* to_usb_serial_port (struct device*) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static ssize_t latency_timer_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct usb_serial_port *port = to_usb_serial_port(dev);
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	if (priv->flags & ASYNC_LOW_LATENCY)
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "%i\n", priv->latency);
}