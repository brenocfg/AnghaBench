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
struct stk_camera {int /*<<< orphan*/  lock; int /*<<< orphan*/  interface; struct file* owner; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stk_camera_write_reg (struct stk_camera*,int,int) ; 
 int /*<<< orphan*/  stk_free_buffers (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_stop_stream (struct stk_camera*) ; 
 int /*<<< orphan*/  unset_initialised (struct stk_camera*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int v4l2_fh_release (struct file*) ; 
 struct stk_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int v4l_stk_release(struct file *fp)
{
	struct stk_camera *dev = video_drvdata(fp);

	mutex_lock(&dev->lock);
	if (dev->owner == fp) {
		stk_stop_stream(dev);
		stk_free_buffers(dev);
		stk_camera_write_reg(dev, 0x0, 0x49); /* turn off the LED */
		unset_initialised(dev);
		dev->owner = NULL;
	}

	usb_autopm_put_interface(dev->interface);
	mutex_unlock(&dev->lock);
	return v4l2_fh_release(fp);
}