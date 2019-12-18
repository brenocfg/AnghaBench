#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct wusb_cbaf_host_info {TYPE_1__ HostFriendlyName_hdr; int /*<<< orphan*/  HostFriendlyName; scalar_t__ LangID; int /*<<< orphan*/  CHID; } ;
struct cbaf {TYPE_4__* usb_iface; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  host_name; int /*<<< orphan*/  chid; struct wusb_cbaf_host_info* buffer; } ;
struct TYPE_8__ {TYPE_3__* cur_altsetting; } ;
struct TYPE_6__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_7__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBAF_REQ_SET_ASSOCIATION_RESPONSE ; 
 int /*<<< orphan*/  CBA_NAME_LEN ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 struct wusb_cbaf_host_info cbaf_host_info_defaults ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  memset (struct wusb_cbaf_host_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct wusb_cbaf_host_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbaf_send_host_info(struct cbaf *cbaf)
{
	struct wusb_cbaf_host_info *hi;
	size_t name_len;
	size_t hi_size;

	hi = cbaf->buffer;
	memset(hi, 0, sizeof(*hi));
	*hi = cbaf_host_info_defaults;
	hi->CHID = cbaf->chid;
	hi->LangID = 0;	/* FIXME: I guess... */
	strlcpy(hi->HostFriendlyName, cbaf->host_name, CBA_NAME_LEN);
	name_len = strlen(cbaf->host_name);
	hi->HostFriendlyName_hdr.len = cpu_to_le16(name_len);
	hi_size = sizeof(*hi) + name_len;

	return usb_control_msg(cbaf->usb_dev,
			usb_sndctrlpipe(cbaf->usb_dev, 0),
			CBAF_REQ_SET_ASSOCIATION_RESPONSE,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			0x0101,
			cbaf->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			hi, hi_size, USB_CTRL_SET_TIMEOUT);
}