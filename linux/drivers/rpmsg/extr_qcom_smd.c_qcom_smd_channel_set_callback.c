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
struct rpmsg_endpoint {int /*<<< orphan*/  cb; } ;
struct qcom_smd_channel {int /*<<< orphan*/  recv_lock; TYPE_1__* qsept; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;
struct TYPE_2__ {struct rpmsg_endpoint ept; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qcom_smd_channel_set_callback(struct qcom_smd_channel *channel,
					  rpmsg_rx_cb_t cb)
{
	struct rpmsg_endpoint *ept = &channel->qsept->ept;
	unsigned long flags;

	spin_lock_irqsave(&channel->recv_lock, flags);
	ept->cb = cb;
	spin_unlock_irqrestore(&channel->recv_lock, flags);
}