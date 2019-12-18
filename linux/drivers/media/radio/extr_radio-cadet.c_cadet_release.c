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
struct cadet {int /*<<< orphan*/  lock; scalar_t__ rdsstat; int /*<<< orphan*/  readtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int cadet_release(struct file *file)
{
	struct cadet *dev = video_drvdata(file);

	mutex_lock(&dev->lock);
	if (v4l2_fh_is_singular_file(file) && dev->rdsstat) {
		del_timer_sync(&dev->readtimer);
		dev->rdsstat = 0;
	}
	v4l2_fh_release(file);
	mutex_unlock(&dev->lock);
	return 0;
}