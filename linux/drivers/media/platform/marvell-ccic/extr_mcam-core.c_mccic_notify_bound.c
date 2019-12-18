#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * v4l2_dev; } ;
struct mcam_camera {int /*<<< orphan*/  s_mutex; struct v4l2_subdev* sensor; TYPE_1__ vdev; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cam_dbg (struct mcam_camera*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_err (struct mcam_camera*,char*) ; 
 int mcam_cam_init (struct mcam_camera*) ; 
 int mcam_setup_vb2 (struct mcam_camera*) ; 
 TYPE_1__ mcam_v4l_template ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mcam_camera* notifier_to_mcam (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_set_subdev_hostdata (struct v4l2_subdev*,struct mcam_camera*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct mcam_camera*) ; 

__attribute__((used)) static int mccic_notify_bound(struct v4l2_async_notifier *notifier,
	struct v4l2_subdev *subdev, struct v4l2_async_subdev *asd)
{
	struct mcam_camera *cam = notifier_to_mcam(notifier);
	int ret;

	mutex_lock(&cam->s_mutex);
	if (cam->sensor) {
		cam_err(cam, "sensor already bound\n");
		ret = -EBUSY;
		goto out;
	}

	v4l2_set_subdev_hostdata(subdev, cam);
	cam->sensor = subdev;

	ret = mcam_cam_init(cam);
	if (ret) {
		cam->sensor = NULL;
		goto out;
	}

	ret = mcam_setup_vb2(cam);
	if (ret) {
		cam->sensor = NULL;
		goto out;
	}

	cam->vdev = mcam_v4l_template;
	cam->vdev.v4l2_dev = &cam->v4l2_dev;
	cam->vdev.lock = &cam->s_mutex;
	cam->vdev.queue = &cam->vb_queue;
	video_set_drvdata(&cam->vdev, cam);
	ret = video_register_device(&cam->vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		cam->sensor = NULL;
		goto out;
	}

	cam_dbg(cam, "sensor %s bound\n", subdev->name);
out:
	mutex_unlock(&cam->s_mutex);
	return ret;
}