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
struct rpmsg_channel_info {void* dst; void* src; int /*<<< orphan*/  name; } ;
struct qcom_glink {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  rcids; int /*<<< orphan*/  dev; } ;
struct glink_channel {int /*<<< orphan*/  refcount; scalar_t__ rcid; int /*<<< orphan*/  name; scalar_t__ rpdev; int /*<<< orphan*/  intent_work; } ;

/* Variables and functions */
 void* RPMSG_ADDR_ANY ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct glink_channel* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_glink_channel_release ; 
 int /*<<< orphan*/  qcom_glink_send_close_ack (struct qcom_glink*,scalar_t__) ; 
 int /*<<< orphan*/  rpmsg_unregister_device (int /*<<< orphan*/ ,struct rpmsg_channel_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qcom_glink_rx_close(struct qcom_glink *glink, unsigned int rcid)
{
	struct rpmsg_channel_info chinfo;
	struct glink_channel *channel;
	unsigned long flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, rcid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	if (WARN(!channel, "close request on unknown channel\n"))
		return;

	/* cancel pending rx_done work */
	cancel_work_sync(&channel->intent_work);

	if (channel->rpdev) {
		strncpy(chinfo.name, channel->name, sizeof(chinfo.name));
		chinfo.src = RPMSG_ADDR_ANY;
		chinfo.dst = RPMSG_ADDR_ANY;

		rpmsg_unregister_device(glink->dev, &chinfo);
	}

	qcom_glink_send_close_ack(glink, channel->rcid);

	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_remove(&glink->rcids, channel->rcid);
	channel->rcid = 0;
	spin_unlock_irqrestore(&glink->idr_lock, flags);

	kref_put(&channel->refcount, qcom_glink_channel_release);
}