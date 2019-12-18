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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int dummy; } ;
struct wusb_port {int change; int /*<<< orphan*/  status; struct wusb_dev* wusb_dev; } ;
struct wusb_dev {int addr; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int USB_PORT_STAT_C_ENABLE ; 
 int USB_PORT_STAT_C_RESET ; 
 int /*<<< orphan*/  USB_PORT_STAT_ENABLE ; 
 int /*<<< orphan*/  USB_PORT_STAT_RESET ; 
 int WUSB_DEV_ADDR_UNAUTH ; 
 int wusb_dev_update_address (struct wusbhc*,struct wusb_dev*) ; 
 struct wusb_port* wusb_port_by_idx (struct wusbhc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wusbhc_rh_port_reset(struct wusbhc *wusbhc, u8 port_idx)
{
	int result = 0;
	struct wusb_port *port = wusb_port_by_idx(wusbhc, port_idx);
	struct wusb_dev *wusb_dev = port->wusb_dev;

	if (wusb_dev == NULL)
		return -ENOTCONN;

	port->status |= USB_PORT_STAT_RESET;
	port->change |= USB_PORT_STAT_C_RESET;

	if (wusb_dev->addr & WUSB_DEV_ADDR_UNAUTH)
		result = 0;
	else
		result = wusb_dev_update_address(wusbhc, wusb_dev);

	port->status &= ~USB_PORT_STAT_RESET;
	port->status |= USB_PORT_STAT_ENABLE;
	port->change |= USB_PORT_STAT_C_RESET | USB_PORT_STAT_C_ENABLE;	

	return result;
}