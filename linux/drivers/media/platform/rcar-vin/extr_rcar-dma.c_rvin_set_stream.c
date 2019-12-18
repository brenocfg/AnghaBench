#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct media_pipeline* pipe; } ;
struct v4l2_subdev {TYPE_4__ entity; } ;
struct TYPE_10__ {struct media_device* mdev; } ;
struct TYPE_13__ {TYPE_3__ graph_obj; } ;
struct media_pipeline {int dummy; } ;
struct TYPE_12__ {TYPE_6__ entity; struct media_pipeline pipe; } ;
struct rvin_dev {TYPE_5__ vdev; int /*<<< orphan*/  pad; TYPE_2__* parallel; TYPE_1__* info; } ;
struct media_pad {int /*<<< orphan*/  entity; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_9__ {struct v4l2_subdev* subdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  use_mc; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int EPIPE ; 
 int __media_pipeline_start (TYPE_6__*,struct media_pipeline*) ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_pipeline_stop (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rvin_mc_validate_format (struct rvin_dev*,struct v4l2_subdev*,struct media_pad*) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int rvin_set_stream(struct rvin_dev *vin, int on)
{
	struct media_pipeline *pipe;
	struct media_device *mdev;
	struct v4l2_subdev *sd;
	struct media_pad *pad;
	int ret;

	/* No media controller used, simply pass operation to subdevice. */
	if (!vin->info->use_mc) {
		ret = v4l2_subdev_call(vin->parallel->subdev, video, s_stream,
				       on);

		return ret == -ENOIOCTLCMD ? 0 : ret;
	}

	pad = media_entity_remote_pad(&vin->pad);
	if (!pad)
		return -EPIPE;

	sd = media_entity_to_v4l2_subdev(pad->entity);

	if (!on) {
		media_pipeline_stop(&vin->vdev.entity);
		return v4l2_subdev_call(sd, video, s_stream, 0);
	}

	ret = rvin_mc_validate_format(vin, sd, pad);
	if (ret)
		return ret;

	/*
	 * The graph lock needs to be taken to protect concurrent
	 * starts of multiple VIN instances as they might share
	 * a common subdevice down the line and then should use
	 * the same pipe.
	 */
	mdev = vin->vdev.entity.graph_obj.mdev;
	mutex_lock(&mdev->graph_mutex);
	pipe = sd->entity.pipe ? sd->entity.pipe : &vin->vdev.pipe;
	ret = __media_pipeline_start(&vin->vdev.entity, pipe);
	mutex_unlock(&mdev->graph_mutex);
	if (ret)
		return ret;

	ret = v4l2_subdev_call(sd, video, s_stream, 1);
	if (ret == -ENOIOCTLCMD)
		ret = 0;
	if (ret)
		media_pipeline_stop(&vin->vdev.entity);

	return ret;
}