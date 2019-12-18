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
struct video_device {int dummy; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/  owner; } ;
struct v4l2_subdev {TYPE_1__* internal_ops; } ;
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct v4l2_subdev*,struct v4l2_subdev_fh*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct v4l2_subdev_fh*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,struct v4l2_subdev_fh*) ; 
 int /*<<< orphan*/  subdev_fh_free (struct v4l2_subdev_fh*) ; 
 struct v4l2_subdev_fh* to_v4l2_subdev_fh (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 struct v4l2_subdev* vdev_to_v4l2_subdev (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int subdev_close(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	struct v4l2_fh *vfh = file->private_data;
	struct v4l2_subdev_fh *subdev_fh = to_v4l2_subdev_fh(vfh);

	if (sd->internal_ops && sd->internal_ops->close)
		sd->internal_ops->close(sd, subdev_fh);
	module_put(subdev_fh->owner);
	v4l2_fh_del(vfh);
	v4l2_fh_exit(vfh);
	subdev_fh_free(subdev_fh);
	kfree(subdev_fh);
	file->private_data = NULL;

	return 0;
}