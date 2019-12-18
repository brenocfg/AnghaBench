#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct isp_ccp2_device {int /*<<< orphan*/  video_in; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_video_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

void omap3isp_ccp2_unregister_entities(struct isp_ccp2_device *ccp2)
{
	v4l2_device_unregister_subdev(&ccp2->subdev);
	omap3isp_video_unregister(&ccp2->video_in);
}