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
struct poll_table_struct {int dummy; } ;
struct fmdev {int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int fmc_is_rds_data_available (struct fmdev*,struct file*,struct poll_table_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t fm_v4l2_fops_poll(struct file *file, struct poll_table_struct *pts)
{
	int ret;
	struct fmdev *fmdev;

	fmdev = video_drvdata(file);
	mutex_lock(&fmdev->mutex);
	ret = fmc_is_rds_data_available(fmdev, file, pts);
	mutex_unlock(&fmdev->mutex);
	if (ret < 0)
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}