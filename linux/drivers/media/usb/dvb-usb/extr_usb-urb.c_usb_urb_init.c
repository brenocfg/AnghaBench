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
struct usb_data_stream_properties {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  endpoint; } ;
struct usb_data_stream {TYPE_1__ props; int /*<<< orphan*/ * complete; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_BULK 129 
#define  USB_ISOC 128 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct usb_data_stream_properties*,int) ; 
 int usb_bulk_urb_init (struct usb_data_stream*) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_isoc_urb_init (struct usb_data_stream*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usb_urb_init(struct usb_data_stream *stream, struct usb_data_stream_properties *props)
{
	if (stream == NULL || props == NULL)
		return -EINVAL;

	memcpy(&stream->props, props, sizeof(*props));

	usb_clear_halt(stream->udev,usb_rcvbulkpipe(stream->udev,stream->props.endpoint));

	if (stream->complete == NULL) {
		err("there is no data callback - this doesn't make sense.");
		return -EINVAL;
	}

	switch (stream->props.type) {
		case USB_BULK:
			return usb_bulk_urb_init(stream);
		case USB_ISOC:
			return usb_isoc_urb_init(stream);
		default:
			err("unknown URB-type for data transfer.");
			return -EINVAL;
	}
}