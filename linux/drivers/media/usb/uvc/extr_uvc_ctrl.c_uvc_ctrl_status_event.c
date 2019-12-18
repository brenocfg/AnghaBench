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
typedef  int /*<<< orphan*/  u8 ;
struct uvc_video_chain {struct uvc_device* dev; } ;
struct uvc_ctrl_work {int /*<<< orphan*/  work; struct uvc_control* ctrl; struct uvc_video_chain* chain; struct urb* urb; int /*<<< orphan*/  const* data; } ;
struct uvc_device {struct uvc_ctrl_work async_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  mappings; } ;
struct uvc_control {int /*<<< orphan*/ * handle; TYPE_1__ info; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

bool uvc_ctrl_status_event(struct urb *urb, struct uvc_video_chain *chain,
			   struct uvc_control *ctrl, const u8 *data)
{
	struct uvc_device *dev = chain->dev;
	struct uvc_ctrl_work *w = &dev->async_ctrl;

	if (list_empty(&ctrl->info.mappings)) {
		ctrl->handle = NULL;
		return false;
	}

	w->data = data;
	w->urb = urb;
	w->chain = chain;
	w->ctrl = ctrl;

	schedule_work(&w->work);

	return true;
}