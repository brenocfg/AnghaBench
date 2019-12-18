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
struct pxa_camera_dev {int /*<<< orphan*/  mlock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pxac_sensor_set_power (struct pxa_camera_dev*,int) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct pxa_camera_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxac_fops_camera_open(struct file *filp)
{
	struct pxa_camera_dev *pcdev = video_drvdata(filp);
	int ret;

	mutex_lock(&pcdev->mlock);
	ret = v4l2_fh_open(filp);
	if (ret < 0)
		goto out;

	if (!v4l2_fh_is_singular_file(filp))
		goto out;

	ret = pxac_sensor_set_power(pcdev, 1);
	if (ret)
		v4l2_fh_release(filp);
out:
	mutex_unlock(&pcdev->mlock);
	return ret;
}