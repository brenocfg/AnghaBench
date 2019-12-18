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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int /*<<< orphan*/  cluster_id; } ;
struct wahc {TYPE_3__* usb_iface; int /*<<< orphan*/  usb_dev; } ;
struct hwahc {struct wahc wa; struct wusbhc wusbhc; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  WUSB_REQ_SET_CLUSTER_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __hwahc_set_cluster_id(struct hwahc *hwahc, u8 cluster_id)
{
	int result;
	struct wusbhc *wusbhc = &hwahc->wusbhc;
	struct wahc *wa = &hwahc->wa;
	struct device *dev = &wa->usb_iface->dev;

	result = usb_control_msg(wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			WUSB_REQ_SET_CLUSTER_ID,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			cluster_id,
			wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (result < 0)
		dev_err(dev, "Cannot set WUSB Cluster ID to 0x%02x: %d\n",
			cluster_id, result);
	else
		wusbhc->cluster_id = cluster_id;
	dev_info(dev, "Wireless USB Cluster ID set to 0x%02x\n", cluster_id);
	return result;
}