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
struct qcom_glink {int dummy; } ;
struct glink_core_rx_intent {int id; size_t size; int reuse; struct glink_core_rx_intent* data; } ;
struct glink_channel {int /*<<< orphan*/  intent_lock; int /*<<< orphan*/  liids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct glink_core_rx_intent*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct glink_core_rx_intent*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct glink_core_rx_intent *
qcom_glink_alloc_intent(struct qcom_glink *glink,
			struct glink_channel *channel,
			size_t size,
			bool reuseable)
{
	struct glink_core_rx_intent *intent;
	int ret;
	unsigned long flags;

	intent = kzalloc(sizeof(*intent), GFP_KERNEL);
	if (!intent)
		return NULL;

	intent->data = kzalloc(size, GFP_KERNEL);
	if (!intent->data)
		goto free_intent;

	spin_lock_irqsave(&channel->intent_lock, flags);
	ret = idr_alloc_cyclic(&channel->liids, intent, 1, -1, GFP_ATOMIC);
	if (ret < 0) {
		spin_unlock_irqrestore(&channel->intent_lock, flags);
		goto free_data;
	}
	spin_unlock_irqrestore(&channel->intent_lock, flags);

	intent->id = ret;
	intent->size = size;
	intent->reuse = reuseable;

	return intent;

free_data:
	kfree(intent->data);
free_intent:
	kfree(intent);
	return NULL;
}