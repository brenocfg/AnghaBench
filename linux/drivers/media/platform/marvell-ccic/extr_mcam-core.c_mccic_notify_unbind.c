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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct mcam_camera {int /*<<< orphan*/  s_mutex; struct v4l2_subdev* sensor; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_dbg (struct mcam_camera*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_err (struct mcam_camera*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mcam_camera* notifier_to_mcam (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mccic_notify_unbind(struct v4l2_async_notifier *notifier,
	struct v4l2_subdev *subdev, struct v4l2_async_subdev *asd)
{
	struct mcam_camera *cam = notifier_to_mcam(notifier);

	mutex_lock(&cam->s_mutex);
	if (cam->sensor != subdev) {
		cam_err(cam, "sensor %s not bound\n", subdev->name);
		goto out;
	}

	video_unregister_device(&cam->vdev);
	cam->sensor = NULL;
	cam_dbg(cam, "sensor %s unbound\n", subdev->name);

out:
	mutex_unlock(&cam->s_mutex);
}