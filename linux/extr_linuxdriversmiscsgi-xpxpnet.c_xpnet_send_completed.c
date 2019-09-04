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
struct xpnet_pending_msg {TYPE_1__* skb; int /*<<< orphan*/  use_count; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct xpnet_pending_msg*) ; 
 int /*<<< orphan*/  xpnet ; 

__attribute__((used)) static void
xpnet_send_completed(enum xp_retval reason, short partid, int channel,
		     void *__qm)
{
	struct xpnet_pending_msg *queued_msg = (struct xpnet_pending_msg *)__qm;

	DBUG_ON(queued_msg == NULL);

	dev_dbg(xpnet, "message to %d notified with reason %d\n",
		partid, reason);

	if (atomic_dec_return(&queued_msg->use_count) == 0) {
		dev_dbg(xpnet, "all acks for skb->head=-x%p\n",
			(void *)queued_msg->skb->head);

		dev_kfree_skb_any(queued_msg->skb);
		kfree(queued_msg);
	}
}