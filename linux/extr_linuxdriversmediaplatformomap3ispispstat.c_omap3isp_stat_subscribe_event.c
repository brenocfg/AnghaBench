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
struct v4l2_event_subscription {scalar_t__ type; } ;
struct ispstat {scalar_t__ event_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STAT_NEVENTS ; 
 int v4l2_event_subscribe (struct v4l2_fh*,struct v4l2_event_subscription*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ispstat* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int omap3isp_stat_subscribe_event(struct v4l2_subdev *subdev,
				  struct v4l2_fh *fh,
				  struct v4l2_event_subscription *sub)
{
	struct ispstat *stat = v4l2_get_subdevdata(subdev);

	if (sub->type != stat->event_type)
		return -EINVAL;

	return v4l2_event_subscribe(fh, sub, STAT_NEVENTS, NULL);
}