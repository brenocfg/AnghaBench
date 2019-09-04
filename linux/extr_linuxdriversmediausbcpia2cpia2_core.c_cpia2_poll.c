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
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_5__ {TYPE_1__ camera_state; } ;
struct camera_data {TYPE_3__* curbuff; int /*<<< orphan*/  wq_stream; TYPE_2__ params; int /*<<< orphan*/  streaming; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_6__ {scalar_t__ status; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ FRAME_READY ; 
 int /*<<< orphan*/  cpia2_usb_stream_start (struct camera_data*,int /*<<< orphan*/ ) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_poll (struct file*,int /*<<< orphan*/ *) ; 

__poll_t cpia2_poll(struct camera_data *cam, struct file *filp,
			poll_table *wait)
{
	__poll_t status = v4l2_ctrl_poll(filp, wait);

	if ((poll_requested_events(wait) & (EPOLLIN | EPOLLRDNORM)) &&
			!cam->streaming) {
		/* Start streaming */
		cpia2_usb_stream_start(cam,
				       cam->params.camera_state.stream_mode);
	}

	poll_wait(filp, &cam->wq_stream, wait);

	if (cam->curbuff->status == FRAME_READY)
		status |= EPOLLIN | EPOLLRDNORM;

	return status;
}