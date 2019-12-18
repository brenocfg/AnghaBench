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
struct file {int dummy; } ;
struct camera_data {int /*<<< orphan*/  v4l2_lock; scalar_t__ COM_len; scalar_t__ APP_len; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 scalar_t__ cpia2_allocate_buffers (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_dbg_dump_registers (struct camera_data*) ; 
 scalar_t__ cpia2_reset_camera (struct camera_data*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_open(struct file *file)
{
	struct camera_data *cam = video_drvdata(file);
	int retval;

	if (mutex_lock_interruptible(&cam->v4l2_lock))
		return -ERESTARTSYS;
	retval = v4l2_fh_open(file);
	if (retval)
		goto open_unlock;

	if (v4l2_fh_is_singular_file(file)) {
		if (cpia2_allocate_buffers(cam)) {
			v4l2_fh_release(file);
			retval = -ENOMEM;
			goto open_unlock;
		}

		/* reset the camera */
		if (cpia2_reset_camera(cam) < 0) {
			v4l2_fh_release(file);
			retval = -EIO;
			goto open_unlock;
		}

		cam->APP_len = 0;
		cam->COM_len = 0;
	}

	cpia2_dbg_dump_registers(cam);
open_unlock:
	mutex_unlock(&cam->v4l2_lock);
	return retval;
}