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
 int EBUSY ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FM_MODE_RX ; 
 int fmc_prepare (struct fmdev*) ; 
 int fmc_set_mode (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radio_disconnected ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_fops_open(struct file *file)
{
	int ret;
	struct fmdev *fmdev = NULL;

	/* Don't allow multiple open */
	if (radio_disconnected) {
		fmerr("FM device is already opened\n");
		return -EBUSY;
	}

	fmdev = video_drvdata(file);

	if (mutex_lock_interruptible(&fmdev->mutex))
		return -ERESTARTSYS;
	ret = fmc_prepare(fmdev);
	if (ret < 0) {
		fmerr("Unable to prepare FM CORE\n");
		goto open_unlock;
	}

	fmdbg("Load FM RX firmware..\n");

	ret = fmc_set_mode(fmdev, FM_MODE_RX);
	if (ret < 0) {
		fmerr("Unable to load FM RX firmware\n");
		goto open_unlock;
	}
	radio_disconnected = 1;

open_unlock:
	mutex_unlock(&fmdev->mutex);
	return ret;
}