#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {TYPE_2__ video; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct iss_csi2_device {TYPE_3__ video_out; TYPE_1__ subdev; } ;
struct iss_device {struct iss_csi2_device csi2b; struct iss_csi2_device csi2a; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_PAD_SOURCE ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap4iss_csi2_create_links(struct iss_device *iss)
{
	struct iss_csi2_device *csi2a = &iss->csi2a;
	struct iss_csi2_device *csi2b = &iss->csi2b;
	int ret;

	/* Connect the CSI2a subdev to the video node. */
	ret = media_create_pad_link(&csi2a->subdev.entity, CSI2_PAD_SOURCE,
				    &csi2a->video_out.video.entity, 0, 0);
	if (ret < 0)
		return ret;

	/* Connect the CSI2b subdev to the video node. */
	ret = media_create_pad_link(&csi2b->subdev.entity, CSI2_PAD_SOURCE,
				    &csi2b->video_out.video.entity, 0, 0);
	if (ret < 0)
		return ret;

	return 0;
}