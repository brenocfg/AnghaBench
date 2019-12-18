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
struct v4l2_dv_timings {int /*<<< orphan*/  bt; int /*<<< orphan*/  type; } ;
struct file {int f_flags; } ;
struct aspeed_video {scalar_t__ v4l2_input_status; int /*<<< orphan*/  detected_timings; int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int ENOLINK ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 int /*<<< orphan*/  VIDEO_RES_CHANGE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aspeed_video* video_drvdata (struct file*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aspeed_video_query_dv_timings(struct file *file, void *fh,
					 struct v4l2_dv_timings *timings)
{
	int rc;
	struct aspeed_video *video = video_drvdata(file);

	/*
	 * This blocks only if the driver is currently in the process of
	 * detecting a new resolution; in the event of no signal or timeout
	 * this function is woken up.
	 */
	if (file->f_flags & O_NONBLOCK) {
		if (test_bit(VIDEO_RES_CHANGE, &video->flags))
			return -EAGAIN;
	} else {
		rc = wait_event_interruptible(video->wait,
					      !test_bit(VIDEO_RES_CHANGE,
							&video->flags));
		if (rc)
			return -EINTR;
	}

	timings->type = V4L2_DV_BT_656_1120;
	timings->bt = video->detected_timings;

	return video->v4l2_input_status ? -ENOLINK : 0;
}