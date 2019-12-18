#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct wusb_cbaf_cc_data {TYPE_2__ CDID; TYPE_1__ CHID; int /*<<< orphan*/  BandGroups; int /*<<< orphan*/  CK; } ;
struct device {int dummy; } ;
struct cbaf {TYPE_5__* usb_iface; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  host_band_groups; int /*<<< orphan*/  ck; TYPE_2__ cdid; TYPE_1__ chid; struct wusb_cbaf_cc_data* buffer; } ;
struct TYPE_10__ {TYPE_4__* cur_altsetting; struct device dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBAF_REQ_SET_ASSOCIATION_RESPONSE ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 struct wusb_cbaf_cc_data cbaf_cc_data_defaults ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct wusb_cbaf_cc_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbaf_cc_upload(struct cbaf *cbaf)
{
	int result;
	struct device *dev = &cbaf->usb_iface->dev;
	struct wusb_cbaf_cc_data *ccd;

	ccd =  cbaf->buffer;
	*ccd = cbaf_cc_data_defaults;
	ccd->CHID = cbaf->chid;
	ccd->CDID = cbaf->cdid;
	ccd->CK = cbaf->ck;
	ccd->BandGroups = cpu_to_le16(cbaf->host_band_groups);

	dev_dbg(dev, "Trying to upload CC:\n");
	dev_dbg(dev, "  CHID       %16ph\n", ccd->CHID.data);
	dev_dbg(dev, "  CDID       %16ph\n", ccd->CDID.data);
	dev_dbg(dev, "  Bandgroups 0x%04x\n", cbaf->host_band_groups);

	result = usb_control_msg(
		cbaf->usb_dev, usb_sndctrlpipe(cbaf->usb_dev, 0),
		CBAF_REQ_SET_ASSOCIATION_RESPONSE,
		USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0x0201, cbaf->usb_iface->cur_altsetting->desc.bInterfaceNumber,
		ccd, sizeof(*ccd), USB_CTRL_SET_TIMEOUT);

	return result;
}