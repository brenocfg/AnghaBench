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
struct video_device {int /*<<< orphan*/ * valid_ioctls; int /*<<< orphan*/  flags; int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_fh {int sequence; int /*<<< orphan*/  subscribe_lock; int /*<<< orphan*/  subscribed; int /*<<< orphan*/  available; int /*<<< orphan*/  wait; int /*<<< orphan*/  prio; struct video_device* vdev; int /*<<< orphan*/  list; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int /*<<< orphan*/  V4L2_PRIORITY_UNSET ; 
 int /*<<< orphan*/  VIDIOC_G_PRIORITY ; 
 int /*<<< orphan*/  VIDIOC_S_PRIORITY ; 
 int /*<<< orphan*/  _IOC_NR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void v4l2_fh_init(struct v4l2_fh *fh, struct video_device *vdev)
{
	fh->vdev = vdev;
	/* Inherit from video_device. May be overridden by the driver. */
	fh->ctrl_handler = vdev->ctrl_handler;
	INIT_LIST_HEAD(&fh->list);
	set_bit(V4L2_FL_USES_V4L2_FH, &fh->vdev->flags);
	/*
	 * determine_valid_ioctls() does not know if struct v4l2_fh
	 * is used by this driver, but here we do. So enable the
	 * prio ioctls here.
	 */
	set_bit(_IOC_NR(VIDIOC_G_PRIORITY), vdev->valid_ioctls);
	set_bit(_IOC_NR(VIDIOC_S_PRIORITY), vdev->valid_ioctls);
	fh->prio = V4L2_PRIORITY_UNSET;
	init_waitqueue_head(&fh->wait);
	INIT_LIST_HEAD(&fh->available);
	INIT_LIST_HEAD(&fh->subscribed);
	fh->sequence = -1;
	mutex_init(&fh->subscribe_lock);
}