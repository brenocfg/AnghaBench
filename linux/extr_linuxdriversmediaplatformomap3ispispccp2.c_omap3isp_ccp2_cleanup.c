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
struct isp_ccp2_device {TYPE_1__ subdev; int /*<<< orphan*/  video_in; } ;
struct isp_device {struct isp_ccp2_device isp_ccp2; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_video_cleanup (int /*<<< orphan*/ *) ; 

void omap3isp_ccp2_cleanup(struct isp_device *isp)
{
	struct isp_ccp2_device *ccp2 = &isp->isp_ccp2;

	omap3isp_video_cleanup(&ccp2->video_in);
	media_entity_cleanup(&ccp2->subdev.entity);
}