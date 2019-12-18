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
struct media_entity {int dummy; } ;
struct fimc_md {TYPE_6__* fimc_is; struct fimc_lite** fimc_lite; } ;
struct TYPE_8__ {struct media_entity entity; } ;
struct TYPE_9__ {TYPE_2__ vdev; } ;
struct TYPE_7__ {struct media_entity entity; } ;
struct fimc_lite {TYPE_3__ ve; TYPE_1__ subdev; } ;
struct TYPE_10__ {struct media_entity entity; } ;
struct TYPE_11__ {TYPE_4__ subdev; } ;
struct TYPE_12__ {TYPE_5__ isp; } ;

/* Variables and functions */
 int FIMC_LITE_MAX_DEVS ; 
 int /*<<< orphan*/  FLITE_SD_PAD_SOURCE_DMA ; 
 int /*<<< orphan*/  FLITE_SD_PAD_SOURCE_ISP ; 
 int media_create_pad_link (struct media_entity*,int /*<<< orphan*/ ,struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __fimc_md_create_flite_source_links(struct fimc_md *fmd)
{
	struct media_entity *source, *sink;
	int i, ret = 0;

	for (i = 0; i < FIMC_LITE_MAX_DEVS; i++) {
		struct fimc_lite *fimc = fmd->fimc_lite[i];

		if (fimc == NULL)
			continue;

		source = &fimc->subdev.entity;
		sink = &fimc->ve.vdev.entity;
		/* FIMC-LITE's subdev and video node */
		ret = media_create_pad_link(source, FLITE_SD_PAD_SOURCE_DMA,
					       sink, 0, 0);
		if (ret)
			break;
		/* Link from FIMC-LITE to IS-ISP subdev */
		sink = &fmd->fimc_is->isp.subdev.entity;
		ret = media_create_pad_link(source, FLITE_SD_PAD_SOURCE_ISP,
					       sink, 0, 0);
		if (ret)
			break;
	}

	return ret;
}