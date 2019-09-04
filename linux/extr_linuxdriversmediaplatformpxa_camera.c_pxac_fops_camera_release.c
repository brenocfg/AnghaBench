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
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pxac_sensor_set_power (struct pxa_camera_dev*,int /*<<< orphan*/ ) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 struct pxa_camera_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxac_fops_camera_release(struct file *filp)
{
	struct pxa_camera_dev *pcdev = video_drvdata(filp);
	int ret;
	bool fh_singular;

	mutex_lock(&pcdev->mlock);

	fh_singular = v4l2_fh_is_singular_file(filp);

	ret = _vb2_fop_release(filp, NULL);

	if (fh_singular)
		ret = pxac_sensor_set_power(pcdev, 0);

	mutex_unlock(&pcdev->mlock);

	return ret;
}