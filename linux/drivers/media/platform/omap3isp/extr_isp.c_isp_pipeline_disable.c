#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {scalar_t__ dev; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {struct media_pad* pads; } ;
struct isp_pipeline {TYPE_2__* output; } ;
struct TYPE_16__ {struct v4l2_subdev subdev; } ;
struct TYPE_15__ {struct v4l2_subdev subdev; } ;
struct TYPE_14__ {struct v4l2_subdev subdev; } ;
struct TYPE_13__ {struct v4l2_subdev subdev; } ;
struct TYPE_12__ {struct v4l2_subdev subdev; } ;
struct TYPE_11__ {struct v4l2_subdev subdev; } ;
struct isp_device {scalar_t__ dev; int stop_failure; int /*<<< orphan*/  crashed; TYPE_8__ isp_prev; TYPE_7__ isp_ccdc; TYPE_6__ isp_res; TYPE_5__ isp_hist; TYPE_4__ isp_af; TYPE_3__ isp_aewb; } ;
struct TYPE_9__ {struct media_entity entity; } ;
struct TYPE_10__ {TYPE_1__ video; struct isp_device* isp; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  dev_info (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 int isp_pipeline_wait (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_pipeline_wait_ccdc ; 
 int /*<<< orphan*/  isp_pipeline_wait_preview ; 
 int /*<<< orphan*/  isp_pipeline_wait_resizer ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int isp_pipeline_disable(struct isp_pipeline *pipe)
{
	struct isp_device *isp = pipe->output->isp;
	struct media_entity *entity;
	struct media_pad *pad;
	struct v4l2_subdev *subdev;
	int failure = 0;
	int ret;

	/*
	 * We need to stop all the modules after CCDC first or they'll
	 * never stop since they may not get a full frame from CCDC.
	 */
	entity = &pipe->output->video.entity;
	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		if (subdev == &isp->isp_ccdc.subdev) {
			v4l2_subdev_call(&isp->isp_aewb.subdev,
					 video, s_stream, 0);
			v4l2_subdev_call(&isp->isp_af.subdev,
					 video, s_stream, 0);
			v4l2_subdev_call(&isp->isp_hist.subdev,
					 video, s_stream, 0);
		}

		ret = v4l2_subdev_call(subdev, video, s_stream, 0);

		if (subdev == &isp->isp_res.subdev)
			ret |= isp_pipeline_wait(isp, isp_pipeline_wait_resizer);
		else if (subdev == &isp->isp_prev.subdev)
			ret |= isp_pipeline_wait(isp, isp_pipeline_wait_preview);
		else if (subdev == &isp->isp_ccdc.subdev)
			ret |= isp_pipeline_wait(isp, isp_pipeline_wait_ccdc);

		/* Handle stop failures. An entity that fails to stop can
		 * usually just be restarted. Flag the stop failure nonetheless
		 * to trigger an ISP reset the next time the device is released,
		 * just in case.
		 *
		 * The preview engine is a special case. A failure to stop can
		 * mean a hardware crash. When that happens the preview engine
		 * won't respond to read/write operations on the L4 bus anymore,
		 * resulting in a bus fault and a kernel oops next time it gets
		 * accessed. Mark it as crashed to prevent pipelines including
		 * it from being started.
		 */
		if (ret) {
			dev_info(isp->dev, "Unable to stop %s\n", subdev->name);
			isp->stop_failure = true;
			if (subdev == &isp->isp_prev.subdev)
				media_entity_enum_set(&isp->crashed,
						      &subdev->entity);
			failure = -ETIMEDOUT;
		}

		/* Stop at the first external sub-device. */
		if (subdev->dev != isp->dev)
			break;
	}

	return failure;
}