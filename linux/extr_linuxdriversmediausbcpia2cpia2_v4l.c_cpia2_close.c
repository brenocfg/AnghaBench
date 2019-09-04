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
struct video_device {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct camera_data {int /*<<< orphan*/  v4l2_lock; scalar_t__ mmapped; int /*<<< orphan*/ * stream_fh; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpia2_free_buffers (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_save_camera_state (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_low_power (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_stop (struct camera_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_release (struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct camera_data* video_get_drvdata (struct video_device*) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpia2_close(struct file *file)
{
	struct video_device *dev = video_devdata(file);
	struct camera_data *cam = video_get_drvdata(dev);

	mutex_lock(&cam->v4l2_lock);
	if (video_is_registered(&cam->vdev) && v4l2_fh_is_singular_file(file)) {
		cpia2_usb_stream_stop(cam);

		/* save camera state for later open */
		cpia2_save_camera_state(cam);

		cpia2_set_low_power(cam);
		cpia2_free_buffers(cam);
	}

	if (cam->stream_fh == file->private_data) {
		cam->stream_fh = NULL;
		cam->mmapped = 0;
	}
	mutex_unlock(&cam->v4l2_lock);
	return v4l2_fh_release(file);
}