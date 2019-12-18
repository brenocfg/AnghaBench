#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct media_entity {int /*<<< orphan*/  name; int /*<<< orphan*/ * pads; } ;
struct fimc_source_info {scalar_t__ fimc_bus_type; } ;
struct fimc_md {int /*<<< orphan*/  v4l2_dev; TYPE_6__** fimc_lite; TYPE_4__** fimc; } ;
struct TYPE_11__ {struct media_entity entity; } ;
struct TYPE_12__ {TYPE_5__ subdev; } ;
struct TYPE_8__ {struct media_entity entity; } ;
struct TYPE_9__ {TYPE_2__ subdev; } ;
struct TYPE_10__ {TYPE_3__ vid_cap; TYPE_1__* variant; } ;
struct TYPE_7__ {int /*<<< orphan*/  has_cam_if; } ;

/* Variables and functions */
 scalar_t__ FIMC_BUS_TYPE_ISP_WRITEBACK ; 
 int FIMC_LITE_MAX_DEVS ; 
 int FIMC_MAX_DEVS ; 
 int /*<<< orphan*/  FIMC_SD_PAD_SINK_CAM ; 
 int /*<<< orphan*/  FLITE_SD_PAD_SINK ; 
 unsigned int MEDIA_LNK_FL_ENABLED ; 
 int /*<<< orphan*/  link_setup ; 
 int media_create_pad_link (struct media_entity*,int,struct media_entity*,int /*<<< orphan*/ ,unsigned int) ; 
 int media_entity_call (struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 struct fimc_source_info* v4l2_get_subdev_hostdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char,...) ; 

__attribute__((used)) static int __fimc_md_create_fimc_sink_links(struct fimc_md *fmd,
					    struct media_entity *source,
					    struct v4l2_subdev *sensor,
					    int pad, int link_mask)
{
	struct fimc_source_info *si = NULL;
	struct media_entity *sink;
	unsigned int flags = 0;
	int i, ret = 0;

	if (sensor) {
		si = v4l2_get_subdev_hostdata(sensor);
		/* Skip direct FIMC links in the logical FIMC-IS sensor path */
		if (si && si->fimc_bus_type == FIMC_BUS_TYPE_ISP_WRITEBACK)
			ret = 1;
	}

	for (i = 0; !ret && i < FIMC_MAX_DEVS; i++) {
		if (!fmd->fimc[i])
			continue;
		/*
		 * Some FIMC variants are not fitted with camera capture
		 * interface. Skip creating a link from sensor for those.
		 */
		if (!fmd->fimc[i]->variant->has_cam_if)
			continue;

		flags = ((1 << i) & link_mask) ? MEDIA_LNK_FL_ENABLED : 0;

		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		ret = media_create_pad_link(source, pad, sink,
					      FIMC_SD_PAD_SINK_CAM, flags);
		if (ret)
			return ret;

		/* Notify FIMC capture subdev entity */
		ret = media_entity_call(sink, link_setup, &sink->pads[0],
					&source->pads[pad], flags);
		if (ret)
			break;

		v4l2_info(&fmd->v4l2_dev, "created link [%s] %c> [%s]\n",
			  source->name, flags ? '=' : '-', sink->name);
	}

	for (i = 0; i < FIMC_LITE_MAX_DEVS; i++) {
		if (!fmd->fimc_lite[i])
			continue;

		sink = &fmd->fimc_lite[i]->subdev.entity;
		ret = media_create_pad_link(source, pad, sink,
					       FLITE_SD_PAD_SINK, 0);
		if (ret)
			return ret;

		/* Notify FIMC-LITE subdev entity */
		ret = media_entity_call(sink, link_setup, &sink->pads[0],
					&source->pads[pad], 0);
		if (ret)
			break;

		v4l2_info(&fmd->v4l2_dev, "created link [%s] -> [%s]\n",
			  source->name, sink->name);
	}
	return 0;
}