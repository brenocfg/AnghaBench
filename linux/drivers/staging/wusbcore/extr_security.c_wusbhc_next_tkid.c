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
typedef  int u32 ;
struct wusbhc {int gtk_tkid; } ;
struct wusb_dev {int addr; int /*<<< orphan*/  port_idx; } ;
struct TYPE_2__ {int ptk_tkid; } ;

/* Variables and functions */
 TYPE_1__* wusb_port_by_idx (struct wusbhc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 wusbhc_next_tkid(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	u32 *tkid;
	u32 addr;

	if (wusb_dev == NULL) {
		tkid = &wusbhc->gtk_tkid;
		addr = 0;
	} else {
		tkid = &wusb_port_by_idx(wusbhc, wusb_dev->port_idx)->ptk_tkid;
		addr = wusb_dev->addr & 0x7f;
	}

	*tkid = (addr << 8) | ((*tkid + 1) & 0xff);

	return *tkid;
}