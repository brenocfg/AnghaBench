#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/  vfh; struct module* owner; } ;
struct TYPE_12__ {TYPE_4__* mdev; } ;
struct TYPE_13__ {TYPE_5__ graph_obj; } ;
struct v4l2_subdev {TYPE_7__* internal_ops; TYPE_6__ entity; TYPE_1__* v4l2_dev; } ;
struct module {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_14__ {int (* open ) (struct v4l2_subdev*,struct v4l2_subdev_fh*) ;} ;
struct TYPE_11__ {TYPE_3__* dev; } ;
struct TYPE_10__ {TYPE_2__* driver; } ;
struct TYPE_9__ {struct module* owner; } ;
struct TYPE_8__ {scalar_t__ mdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct v4l2_subdev_fh*) ; 
 struct v4l2_subdev_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int stub1 (struct v4l2_subdev*,struct v4l2_subdev_fh*) ; 
 int /*<<< orphan*/  subdev_fh_free (struct v4l2_subdev_fh*) ; 
 int subdev_fh_init (struct v4l2_subdev_fh*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 struct v4l2_subdev* vdev_to_v4l2_subdev (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int subdev_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	struct v4l2_subdev_fh *subdev_fh;
	int ret;

	subdev_fh = kzalloc(sizeof(*subdev_fh), GFP_KERNEL);
	if (subdev_fh == NULL)
		return -ENOMEM;

	ret = subdev_fh_init(subdev_fh, sd);
	if (ret) {
		kfree(subdev_fh);
		return ret;
	}

	v4l2_fh_init(&subdev_fh->vfh, vdev);
	v4l2_fh_add(&subdev_fh->vfh);
	file->private_data = &subdev_fh->vfh;
#if defined(CONFIG_MEDIA_CONTROLLER)
	if (sd->v4l2_dev->mdev && sd->entity.graph_obj.mdev->dev) {
		struct module *owner;

		owner = sd->entity.graph_obj.mdev->dev->driver->owner;
		if (!try_module_get(owner)) {
			ret = -EBUSY;
			goto err;
		}
		subdev_fh->owner = owner;
	}
#endif

	if (sd->internal_ops && sd->internal_ops->open) {
		ret = sd->internal_ops->open(sd, subdev_fh);
		if (ret < 0)
			goto err;
	}

	return 0;

err:
	module_put(subdev_fh->owner);
	v4l2_fh_del(&subdev_fh->vfh);
	v4l2_fh_exit(&subdev_fh->vfh);
	subdev_fh_free(subdev_fh);
	kfree(subdev_fh);

	return ret;
}