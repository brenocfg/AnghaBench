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
struct rpmsg_endpoint {int dummy; } ;
struct qcom_glink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cb; } ;
struct glink_channel {int /*<<< orphan*/ * rpdev; int /*<<< orphan*/  recv_lock; TYPE_1__ ept; struct qcom_glink* glink; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_glink_send_close_req (struct qcom_glink*,struct glink_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct glink_channel* to_glink_channel (struct rpmsg_endpoint*) ; 

__attribute__((used)) static void qcom_glink_destroy_ept(struct rpmsg_endpoint *ept)
{
	struct glink_channel *channel = to_glink_channel(ept);
	struct qcom_glink *glink = channel->glink;
	unsigned long flags;

	spin_lock_irqsave(&channel->recv_lock, flags);
	channel->ept.cb = NULL;
	spin_unlock_irqrestore(&channel->recv_lock, flags);

	/* Decouple the potential rpdev from the channel */
	channel->rpdev = NULL;

	qcom_glink_send_close_req(glink, channel);
}