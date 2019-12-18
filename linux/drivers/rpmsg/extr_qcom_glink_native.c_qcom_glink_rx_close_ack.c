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
struct qcom_glink {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  lcids; } ;
struct glink_channel {int /*<<< orphan*/  refcount; scalar_t__ lcid; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*) ; 
 struct glink_channel* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_glink_channel_release ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qcom_glink_rx_close_ack(struct qcom_glink *glink, unsigned int lcid)
{
	struct glink_channel *channel;
	unsigned long flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->lcids, lcid);
	if (WARN(!channel, "close ack on unknown channel\n")) {
		spin_unlock_irqrestore(&glink->idr_lock, flags);
		return;
	}

	idr_remove(&glink->lcids, channel->lcid);
	channel->lcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	kref_put(&channel->refcount, qcom_glink_channel_release);
}