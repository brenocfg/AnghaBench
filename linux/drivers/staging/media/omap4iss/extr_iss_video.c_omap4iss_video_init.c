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
struct TYPE_5__ {int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  release; int /*<<< orphan*/  vfl_type; int /*<<< orphan*/  name; int /*<<< orphan*/ * fops; int /*<<< orphan*/  entity; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_state; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct iss_video {int type; TYPE_2__ video; TYPE_1__ pipe; int /*<<< orphan*/ * ops; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/  active; int /*<<< orphan*/  mutex; int /*<<< orphan*/  qlock; TYPE_3__ pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISS_PIPELINE_STREAM_STOPPED ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_video_dummy_ops ; 
 int /*<<< orphan*/  iss_video_fops ; 
 int /*<<< orphan*/  iss_video_ioctl_ops ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct iss_video*) ; 

int omap4iss_video_init(struct iss_video *video, const char *name)
{
	const char *direction;
	int ret;

	switch (video->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		direction = "output";
		video->pad.flags = MEDIA_PAD_FL_SINK;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		direction = "input";
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		break;

	default:
		return -EINVAL;
	}

	ret = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	if (ret < 0)
		return ret;

	spin_lock_init(&video->qlock);
	mutex_init(&video->mutex);
	atomic_set(&video->active, 0);

	spin_lock_init(&video->pipe.lock);
	mutex_init(&video->stream_lock);

	/* Initialize the video device. */
	if (!video->ops)
		video->ops = &iss_video_dummy_ops;

	video->video.fops = &iss_video_fops;
	snprintf(video->video.name, sizeof(video->video.name),
		 "OMAP4 ISS %s %s", name, direction);
	video->video.vfl_type = VFL_TYPE_GRABBER;
	video->video.release = video_device_release_empty;
	video->video.ioctl_ops = &iss_video_ioctl_ops;
	video->pipe.stream_state = ISS_PIPELINE_STREAM_STOPPED;

	video_set_drvdata(&video->video, video);

	return 0;
}