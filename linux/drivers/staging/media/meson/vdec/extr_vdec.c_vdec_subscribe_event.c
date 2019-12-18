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
struct v4l2_fh {int dummy; } ;
struct v4l2_event_subscription {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_EVENT_CTRL 130 
#define  V4L2_EVENT_EOS 129 
#define  V4L2_EVENT_SOURCE_CHANGE 128 
 int v4l2_ctrl_subscribe_event (struct v4l2_fh*,struct v4l2_event_subscription const*) ; 
 int v4l2_event_subscribe (struct v4l2_fh*,struct v4l2_event_subscription const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdec_subscribe_event(struct v4l2_fh *fh,
				const struct v4l2_event_subscription *sub)
{
	switch (sub->type) {
	case V4L2_EVENT_EOS:
	case V4L2_EVENT_SOURCE_CHANGE:
		return v4l2_event_subscribe(fh, sub, 0, NULL);
	case V4L2_EVENT_CTRL:
		return v4l2_ctrl_subscribe_event(fh, sub);
	default:
		return -EINVAL;
	}
}