#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {struct device* dev; } ;
struct wusb_dev {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int bLength; int /*<<< orphan*/  bIEIdentifier; } ;
struct wuie_disconnect {TYPE_1__ hdr; int /*<<< orphan*/  bDeviceAddress; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct wusb_dev* wusb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WUIE_ID_DEVICE_DISCONNECT ; 
 int /*<<< orphan*/  __wusbhc_dev_disconnect (struct wusbhc*,TYPE_3__*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct wuie_disconnect*) ; 
 struct wuie_disconnect* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_3__* wusb_port_by_idx (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusbhc_mmcie_rm (struct wusbhc*,TYPE_1__*) ; 
 int wusbhc_mmcie_set (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void __wusbhc_dev_disable(struct wusbhc *wusbhc, u8 port_idx)
{
	int result;
	struct device *dev = wusbhc->dev;
	struct wusb_dev *wusb_dev;
	struct wuie_disconnect *ie;

	wusb_dev = wusb_port_by_idx(wusbhc, port_idx)->wusb_dev;
	if (wusb_dev == NULL) {
		/* reset no device? ignore */
		dev_dbg(dev, "DISCONNECT: no device at port %u, ignoring\n",
			port_idx);
		return;
	}
	__wusbhc_dev_disconnect(wusbhc, wusb_port_by_idx(wusbhc, port_idx));

	ie = kzalloc(sizeof(*ie), GFP_KERNEL);
	if (ie == NULL)
		return;
	ie->hdr.bLength = sizeof(*ie);
	ie->hdr.bIEIdentifier = WUIE_ID_DEVICE_DISCONNECT;
	ie->bDeviceAddress = wusb_dev->addr;
	result = wusbhc_mmcie_set(wusbhc, 0, 0, &ie->hdr);
	if (result < 0)
		dev_err(dev, "DISCONNECT: can't set MMC: %d\n", result);
	else {
		/* At least 6 MMCs, assuming at least 1 MMC per zone. */
		msleep(7*4);
		wusbhc_mmcie_rm(wusbhc, &ie->hdr);
	}
	kfree(ie);
}