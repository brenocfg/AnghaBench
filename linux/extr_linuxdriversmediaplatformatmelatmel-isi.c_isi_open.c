#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* subdev; } ;
struct atmel_isi {int /*<<< orphan*/  lock; int /*<<< orphan*/  fmt; TYPE_1__ entity; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  core ; 
 int isi_set_fmt (struct atmel_isi*,int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct atmel_isi* video_drvdata (struct file*) ; 

__attribute__((used)) static int isi_open(struct file *file)
{
	struct atmel_isi *isi = video_drvdata(file);
	struct v4l2_subdev *sd = isi->entity.subdev;
	int ret;

	if (mutex_lock_interruptible(&isi->lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	if (!v4l2_fh_is_singular_file(file))
		goto fh_rel;

	ret = v4l2_subdev_call(sd, core, s_power, 1);
	if (ret < 0 && ret != -ENOIOCTLCMD)
		goto fh_rel;

	ret = isi_set_fmt(isi, &isi->fmt);
	if (ret)
		v4l2_subdev_call(sd, core, s_power, 0);
fh_rel:
	if (ret)
		v4l2_fh_release(file);
unlock:
	mutex_unlock(&isi->lock);
	return ret;
}