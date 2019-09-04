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
struct fmdev {int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MODE_OFF ; 
 int fmc_release (struct fmdev*) ; 
 int fmc_set_mode (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ radio_disconnected ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_fops_release(struct file *file)
{
	int ret;
	struct fmdev *fmdev;

	fmdev = video_drvdata(file);
	if (!radio_disconnected) {
		fmdbg("FM device is already closed\n");
		return 0;
	}

	mutex_lock(&fmdev->mutex);
	ret = fmc_set_mode(fmdev, FM_MODE_OFF);
	if (ret < 0) {
		fmerr("Unable to turn off the chip\n");
		goto release_unlock;
	}

	ret = fmc_release(fmdev);
	if (ret < 0) {
		fmerr("FM CORE release failed\n");
		goto release_unlock;
	}
	radio_disconnected = 0;

release_unlock:
	mutex_unlock(&fmdev->mutex);
	return ret;
}