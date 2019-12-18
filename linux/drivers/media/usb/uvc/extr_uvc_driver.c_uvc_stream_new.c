#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uvc_streaming {int /*<<< orphan*/  async_wq; int /*<<< orphan*/  intfnum; int /*<<< orphan*/  intf; struct uvc_device* dev; int /*<<< orphan*/  mutex; } ;
struct uvc_device {int dummy; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WQ_HIGHPRI ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 struct uvc_streaming* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  uvc_stream_delete (struct uvc_streaming*) ; 

__attribute__((used)) static struct uvc_streaming *uvc_stream_new(struct uvc_device *dev,
					    struct usb_interface *intf)
{
	struct uvc_streaming *stream;

	stream = kzalloc(sizeof(*stream), GFP_KERNEL);
	if (stream == NULL)
		return NULL;

	mutex_init(&stream->mutex);

	stream->dev = dev;
	stream->intf = usb_get_intf(intf);
	stream->intfnum = intf->cur_altsetting->desc.bInterfaceNumber;

	/* Allocate a stream specific work queue for asynchronous tasks. */
	stream->async_wq = alloc_workqueue("uvcvideo", WQ_UNBOUND | WQ_HIGHPRI,
					   0);
	if (!stream->async_wq) {
		uvc_stream_delete(stream);
		return NULL;
	}

	return stream;
}