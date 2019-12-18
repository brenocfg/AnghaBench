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
typedef  unsigned int u16 ;
struct usb_port {int /*<<< orphan*/  dev; } ;
struct usb_hub {int /*<<< orphan*/  hdev; struct usb_port** ports; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HUB_DEBOUNCE_STABLE ; 
 scalar_t__ HUB_DEBOUNCE_STEP ; 
 int HUB_DEBOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  USB_PORT_FEAT_C_CONNECTION ; 
 unsigned int USB_PORT_STAT_CONNECTION ; 
 unsigned int USB_PORT_STAT_C_CONNECTION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,unsigned int) ; 
 int hub_port_status (struct usb_hub*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  usb_clear_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int hub_port_debounce(struct usb_hub *hub, int port1, bool must_be_connected)
{
	int ret;
	u16 portchange, portstatus;
	unsigned connection = 0xffff;
	int total_time, stable_time = 0;
	struct usb_port *port_dev = hub->ports[port1 - 1];

	for (total_time = 0; ; total_time += HUB_DEBOUNCE_STEP) {
		ret = hub_port_status(hub, port1, &portstatus, &portchange);
		if (ret < 0)
			return ret;

		if (!(portchange & USB_PORT_STAT_C_CONNECTION) &&
		     (portstatus & USB_PORT_STAT_CONNECTION) == connection) {
			if (!must_be_connected ||
			     (connection == USB_PORT_STAT_CONNECTION))
				stable_time += HUB_DEBOUNCE_STEP;
			if (stable_time >= HUB_DEBOUNCE_STABLE)
				break;
		} else {
			stable_time = 0;
			connection = portstatus & USB_PORT_STAT_CONNECTION;
		}

		if (portchange & USB_PORT_STAT_C_CONNECTION) {
			usb_clear_port_feature(hub->hdev, port1,
					USB_PORT_FEAT_C_CONNECTION);
		}

		if (total_time >= HUB_DEBOUNCE_TIMEOUT)
			break;
		msleep(HUB_DEBOUNCE_STEP);
	}

	dev_dbg(&port_dev->dev, "debounce total %dms stable %dms status 0x%x\n",
			total_time, stable_time, portstatus);

	if (stable_time < HUB_DEBOUNCE_STABLE)
		return -ETIMEDOUT;
	return portstatus;
}