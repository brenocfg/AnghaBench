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
struct v4l2_subdev {int dummy; } ;
struct v4l2_fh {int dummy; } ;
struct v4l2_event_subscription {scalar_t__ type; scalar_t__ id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP3ISP_CCDC_NEVENTS ; 
 scalar_t__ V4L2_EVENT_FRAME_SYNC ; 
 int v4l2_event_subscribe (struct v4l2_fh*,struct v4l2_event_subscription*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccdc_subscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				struct v4l2_event_subscription *sub)
{
	if (sub->type != V4L2_EVENT_FRAME_SYNC)
		return -EINVAL;

	/* line number is zero at frame start */
	if (sub->id != 0)
		return -EINVAL;

	return v4l2_event_subscribe(fh, sub, OMAP3ISP_CCDC_NEVENTS, NULL);
}