#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct framebuf {scalar_t__ status; scalar_t__ length; } ;
struct camera_data {int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  streaming; int /*<<< orphan*/  wq_stream; struct framebuf* buffers; } ;

/* Variables and functions */
 int ENOTTY ; 
 int ERESTARTSYS ; 
 scalar_t__ FRAME_READY ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sync(struct camera_data *cam, int frame_nr)
{
	struct framebuf *frame = &cam->buffers[frame_nr];

	while (1) {
		if (frame->status == FRAME_READY)
			return 0;

		if (!cam->streaming) {
			frame->status = FRAME_READY;
			frame->length = 0;
			return 0;
		}

		mutex_unlock(&cam->v4l2_lock);
		wait_event_interruptible(cam->wq_stream,
					 !cam->streaming ||
					 frame->status == FRAME_READY);
		mutex_lock(&cam->v4l2_lock);
		if (signal_pending(current))
			return -ERESTARTSYS;
		if (!video_is_registered(&cam->vdev))
			return -ENOTTY;
	}
}