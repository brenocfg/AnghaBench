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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_csi2_device {TYPE_1__ subdev; int /*<<< orphan*/  video_out; } ;
struct isp_device {struct isp_csi2_device isp_csi2a; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_video_cleanup (int /*<<< orphan*/ *) ; 

void omap3isp_csi2_cleanup(struct isp_device *isp)
{
	struct isp_csi2_device *csi2a = &isp->isp_csi2a;

	omap3isp_video_cleanup(&csi2a->video_out);
	media_entity_cleanup(&csi2a->subdev.entity);
}