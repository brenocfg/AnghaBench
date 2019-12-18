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
struct usb_port {int /*<<< orphan*/  dev; } ;
struct usb_hub {int /*<<< orphan*/  hdev; struct usb_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_INDICATOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int set_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_led_name (int) ; 

__attribute__((used)) static void set_port_led(struct usb_hub *hub, int port1, int selector)
{
	struct usb_port *port_dev = hub->ports[port1 - 1];
	int status;

	status = set_port_feature(hub->hdev, (selector << 8) | port1,
			USB_PORT_FEAT_INDICATOR);
	dev_dbg(&port_dev->dev, "indicator %s status %d\n",
		to_led_name(selector), status);
}