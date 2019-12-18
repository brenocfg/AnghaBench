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
struct usb_interface {int /*<<< orphan*/  dev; TYPE_1__* altsetting; } ;
typedef  struct usb_cdc_union_desc {size_t bLength; scalar_t__ bDescriptorType; scalar_t__ bDescriptorSubType; } const usb_cdc_union_desc ;
struct TYPE_2__ {void* extra; size_t extralen; } ;

/* Variables and functions */
 scalar_t__ USB_CDC_UNION_TYPE ; 
 scalar_t__ USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static const struct usb_cdc_union_desc *
ims_pcu_get_cdc_union_desc(struct usb_interface *intf)
{
	const void *buf = intf->altsetting->extra;
	size_t buflen = intf->altsetting->extralen;
	struct usb_cdc_union_desc *union_desc;

	if (!buf) {
		dev_err(&intf->dev, "Missing descriptor data\n");
		return NULL;
	}

	if (!buflen) {
		dev_err(&intf->dev, "Zero length descriptor\n");
		return NULL;
	}

	while (buflen >= sizeof(*union_desc)) {
		union_desc = (struct usb_cdc_union_desc *)buf;

		if (union_desc->bLength > buflen) {
			dev_err(&intf->dev, "Too large descriptor\n");
			return NULL;
		}

		if (union_desc->bDescriptorType == USB_DT_CS_INTERFACE &&
		    union_desc->bDescriptorSubType == USB_CDC_UNION_TYPE) {
			dev_dbg(&intf->dev, "Found union header\n");

			if (union_desc->bLength >= sizeof(*union_desc))
				return union_desc;

			dev_err(&intf->dev,
				"Union descriptor too short (%d vs %zd)\n",
				union_desc->bLength, sizeof(*union_desc));
			return NULL;
		}

		buflen -= union_desc->bLength;
		buf += union_desc->bLength;
	}

	dev_err(&intf->dev, "Missing CDC union descriptor\n");
	return NULL;
}