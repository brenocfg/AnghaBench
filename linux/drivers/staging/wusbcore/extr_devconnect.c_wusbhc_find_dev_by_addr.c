#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wusbhc {int ports_max; } ;
struct wusb_dev {int addr; } ;
struct TYPE_2__ {struct wusb_dev* wusb_dev; } ;

/* Variables and functions */
 TYPE_1__* wusb_port_by_idx (struct wusbhc*,int) ; 

__attribute__((used)) static struct wusb_dev *wusbhc_find_dev_by_addr(struct wusbhc *wusbhc, u8 addr)
{
	int p;

	if (addr == 0xff) /* unconnected */
		return NULL;

	if (addr > 0) {
		int port = (addr & ~0x80) - 2;
		if (port < 0 || port >= wusbhc->ports_max)
			return NULL;
		return wusb_port_by_idx(wusbhc, port)->wusb_dev;
	}

	/* Look for the device with address 0. */
	for (p = 0; p < wusbhc->ports_max; p++) {
		struct wusb_dev *wusb_dev = wusb_port_by_idx(wusbhc, p)->wusb_dev;
		if (wusb_dev && wusb_dev->addr == addr)
			return wusb_dev;
	}
	return NULL;
}