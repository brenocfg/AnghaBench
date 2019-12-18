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
struct hdpvr_device {scalar_t__ owner; int /*<<< orphan*/  io_mutex; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdpvr_stop_streaming (struct hdpvr_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_fh_release (struct file*) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int hdpvr_release(struct file *file)
{
	struct hdpvr_device *dev = video_drvdata(file);

	mutex_lock(&dev->io_mutex);
	if (file->private_data == dev->owner) {
		hdpvr_stop_streaming(dev);
		dev->owner = NULL;
	}
	mutex_unlock(&dev->io_mutex);

	return v4l2_fh_release(file);
}