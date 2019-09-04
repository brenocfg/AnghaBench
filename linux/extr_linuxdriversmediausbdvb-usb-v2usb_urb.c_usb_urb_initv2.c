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
struct usb_data_stream_properties {int dummy; } ;
struct TYPE_7__ {int framesize; int framesperurb; } ;
struct TYPE_6__ {int buffersize; } ;
struct TYPE_8__ {TYPE_2__ isoc; TYPE_1__ bulk; } ;
struct TYPE_10__ {int type; TYPE_3__ u; int /*<<< orphan*/  count; } ;
struct usb_data_stream {TYPE_4__* udev; TYPE_5__ props; int /*<<< orphan*/  complete; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
#define  USB_BULK 129 
#define  USB_ISOC 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,struct usb_data_stream_properties const*,int) ; 
 int usb_alloc_stream_buffers (struct usb_data_stream*,int /*<<< orphan*/ ,int) ; 
 int usb_urb_alloc_bulk_urbs (struct usb_data_stream*) ; 
 int usb_urb_alloc_isoc_urbs (struct usb_data_stream*) ; 

int usb_urb_initv2(struct usb_data_stream *stream,
		const struct usb_data_stream_properties *props)
{
	int ret;

	if (!stream || !props)
		return -EINVAL;

	memcpy(&stream->props, props, sizeof(*props));

	if (!stream->complete) {
		dev_err(&stream->udev->dev,
				"%s: there is no data callback - this doesn't make sense\n",
				KBUILD_MODNAME);
		return -EINVAL;
	}

	switch (stream->props.type) {
	case USB_BULK:
		ret = usb_alloc_stream_buffers(stream, stream->props.count,
				stream->props.u.bulk.buffersize);
		if (ret < 0)
			return ret;

		return usb_urb_alloc_bulk_urbs(stream);
	case USB_ISOC:
		ret = usb_alloc_stream_buffers(stream, stream->props.count,
				stream->props.u.isoc.framesize *
				stream->props.u.isoc.framesperurb);
		if (ret < 0)
			return ret;

		return usb_urb_alloc_isoc_urbs(stream);
	default:
		dev_err(&stream->udev->dev,
				"%s: unknown urb-type for data transfer\n",
				KBUILD_MODNAME);
		return -EINVAL;
	}
}