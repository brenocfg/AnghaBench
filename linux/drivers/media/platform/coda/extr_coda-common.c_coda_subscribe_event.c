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
struct coda_ctx {int /*<<< orphan*/  inst_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_INST_DECODER ; 
 int EINVAL ; 
#define  V4L2_EVENT_EOS 129 
#define  V4L2_EVENT_SOURCE_CHANGE 128 
 struct coda_ctx* fh_to_ctx (struct v4l2_fh*) ; 
 int v4l2_ctrl_subscribe_event (struct v4l2_fh*,struct v4l2_event_subscription const*) ; 
 int v4l2_event_subscribe (struct v4l2_fh*,struct v4l2_event_subscription const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_subscribe_event(struct v4l2_fh *fh,
				const struct v4l2_event_subscription *sub)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);

	switch (sub->type) {
	case V4L2_EVENT_EOS:
		return v4l2_event_subscribe(fh, sub, 0, NULL);
	case V4L2_EVENT_SOURCE_CHANGE:
		if (ctx->inst_type == CODA_INST_DECODER)
			return v4l2_event_subscribe(fh, sub, 0, NULL);
		else
			return -EINVAL;
	default:
		return v4l2_ctrl_subscribe_event(fh, sub);
	}
}