#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  entity; } ;
struct TYPE_9__ {TYPE_3__* sd; } ;
struct camif_dev {TYPE_2__* vp; TYPE_5__ subdev; TYPE_4__ sensor; } ;
struct TYPE_8__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct TYPE_7__ {TYPE_1__ vdev; } ;

/* Variables and functions */
 int CAMIF_SD_PADS_NUM ; 
 int /*<<< orphan*/  CAMIF_SD_PAD_SINK ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int camif_create_media_links(struct camif_dev *camif)
{
	int i, ret;

	ret = media_create_pad_link(&camif->sensor.sd->entity, 0,
				&camif->subdev.entity, CAMIF_SD_PAD_SINK,
				MEDIA_LNK_FL_IMMUTABLE |
				MEDIA_LNK_FL_ENABLED);
	if (ret)
		return ret;

	for (i = 1; i < CAMIF_SD_PADS_NUM && !ret; i++) {
		ret = media_create_pad_link(&camif->subdev.entity, i,
				&camif->vp[i - 1].vdev.entity, 0,
				MEDIA_LNK_FL_IMMUTABLE |
				MEDIA_LNK_FL_ENABLED);
	}

	return ret;
}