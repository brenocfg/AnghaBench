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
struct media_entity {scalar_t__ num_pads; } ;
struct fimc_md {TYPE_5__** fimc; TYPE_1__* fimc_is; } ;
struct TYPE_14__ {struct media_entity entity; } ;
struct TYPE_15__ {TYPE_6__ vdev; } ;
struct TYPE_16__ {TYPE_7__ ve; } ;
struct TYPE_10__ {struct media_entity entity; } ;
struct fimc_isp {TYPE_8__ video_capture; TYPE_2__ subdev; } ;
struct TYPE_11__ {struct media_entity entity; } ;
struct TYPE_12__ {TYPE_3__ subdev; } ;
struct TYPE_13__ {TYPE_4__ vid_cap; } ;
struct TYPE_9__ {struct fimc_isp isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIMC_ISP_SD_PAD_SRC_DMA ; 
 int /*<<< orphan*/  FIMC_ISP_SD_PAD_SRC_FIFO ; 
 int FIMC_MAX_DEVS ; 
 int /*<<< orphan*/  FIMC_SD_PAD_SINK_FIFO ; 
 int media_create_pad_link (struct media_entity*,int /*<<< orphan*/ ,struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __fimc_md_create_fimc_is_links(struct fimc_md *fmd)
{
	struct fimc_isp *isp = &fmd->fimc_is->isp;
	struct media_entity *source, *sink;
	int i, ret;

	source = &isp->subdev.entity;

	for (i = 0; i < FIMC_MAX_DEVS; i++) {
		if (fmd->fimc[i] == NULL)
			continue;

		/* Link from FIMC-IS-ISP subdev to FIMC */
		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		ret = media_create_pad_link(source, FIMC_ISP_SD_PAD_SRC_FIFO,
					       sink, FIMC_SD_PAD_SINK_FIFO, 0);
		if (ret)
			return ret;
	}

	/* Link from FIMC-IS-ISP subdev to fimc-is-isp.capture video node */
	sink = &isp->video_capture.ve.vdev.entity;

	/* Skip this link if the fimc-is-isp video node driver isn't built-in */
	if (sink->num_pads == 0)
		return 0;

	return media_create_pad_link(source, FIMC_ISP_SD_PAD_SRC_DMA,
					sink, 0, 0);
}