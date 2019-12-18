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
typedef  int /*<<< orphan*/  v4l2_event ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct v4l2_event {int /*<<< orphan*/  type; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct uvc_event {TYPE_2__ data; } ;
struct uvc_device {int /*<<< orphan*/  vdev; scalar_t__ event_setup_out; } ;
struct usb_request {int /*<<< orphan*/  actual; int /*<<< orphan*/  buf; struct uvc_device* context; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_EVENT_DATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ *,struct v4l2_event*) ; 

__attribute__((used)) static void
uvc_function_ep0_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct uvc_device *uvc = req->context;
	struct v4l2_event v4l2_event;
	struct uvc_event *uvc_event = (void *)&v4l2_event.u.data;

	if (uvc->event_setup_out) {
		uvc->event_setup_out = 0;

		memset(&v4l2_event, 0, sizeof(v4l2_event));
		v4l2_event.type = UVC_EVENT_DATA;
		uvc_event->data.length = req->actual;
		memcpy(&uvc_event->data.data, req->buf, req->actual);
		v4l2_event_queue(&uvc->vdev, &v4l2_event);
	}
}