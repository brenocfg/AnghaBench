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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct qcom_glink {int /*<<< orphan*/  dev; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  rcids; } ;
struct glink_core_rx_intent {int in_use; int /*<<< orphan*/  id; } ;
struct glink_channel {int /*<<< orphan*/  intent_lock; int /*<<< orphan*/  riids; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct glink_core_rx_intent*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qcom_glink_handle_rx_done(struct qcom_glink *glink,
				      u32 cid, uint32_t iid,
				      bool reuse)
{
	struct glink_core_rx_intent *intent;
	struct glink_channel *channel;
	unsigned long flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	if (!channel) {
		dev_err(glink->dev, "invalid channel id received\n");
		return;
	}

	spin_lock_irqsave(&channel->intent_lock, flags);
	intent = idr_find(&channel->riids, iid);

	if (!intent) {
		spin_unlock_irqrestore(&channel->intent_lock, flags);
		dev_err(glink->dev, "invalid intent id received\n");
		return;
	}

	intent->in_use = false;

	if (!reuse) {
		idr_remove(&channel->riids, intent->id);
		kfree(intent);
	}
	spin_unlock_irqrestore(&channel->intent_lock, flags);
}