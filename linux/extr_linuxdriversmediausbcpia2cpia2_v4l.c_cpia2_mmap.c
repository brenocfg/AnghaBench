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
struct vm_area_struct {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct camera_data {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  stream_fh; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int cpia2_remap_buffer (struct camera_data*,struct vm_area_struct*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_mmap(struct file *file, struct vm_area_struct *area)
{
	struct camera_data *cam = video_drvdata(file);
	int retval;

	if (mutex_lock_interruptible(&cam->v4l2_lock))
		return -ERESTARTSYS;
	retval = cpia2_remap_buffer(cam, area);

	if(!retval)
		cam->stream_fh = file->private_data;
	mutex_unlock(&cam->v4l2_lock);
	return retval;
}