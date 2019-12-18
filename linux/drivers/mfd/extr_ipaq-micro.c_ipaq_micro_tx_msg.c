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
struct ipaq_micro_msg {int /*<<< orphan*/  node; int /*<<< orphan*/  tx_len; int /*<<< orphan*/  id; } ;
struct ipaq_micro {int /*<<< orphan*/  lock; struct ipaq_micro_msg* msg; int /*<<< orphan*/  queue; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaq_micro_trigger_tx (struct ipaq_micro*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipaq_micro_tx_msg(struct ipaq_micro *micro, struct ipaq_micro_msg *msg)
{
	unsigned long flags;

	dev_dbg(micro->dev, "TX msg: %02x, %d bytes\n", msg->id, msg->tx_len);

	spin_lock_irqsave(&micro->lock, flags);
	if (micro->msg) {
		list_add_tail(&msg->node, &micro->queue);
		spin_unlock_irqrestore(&micro->lock, flags);
		return 0;
	}
	micro->msg = msg;
	ipaq_micro_trigger_tx(micro);
	spin_unlock_irqrestore(&micro->lock, flags);
	return 0;
}