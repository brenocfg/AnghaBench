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
struct sk_buff {int dummy; } ;
struct i2400m {int /*<<< orphan*/  rx_lock; struct sk_buff* ack_skb; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i2400m_msg_to_dev_cancel_wait(struct i2400m *i2400m, int code)
{
	struct sk_buff *ack_skb;
	unsigned long flags;

	spin_lock_irqsave(&i2400m->rx_lock, flags);
	ack_skb = i2400m->ack_skb;
	if (ack_skb && !IS_ERR(ack_skb))
		kfree_skb(ack_skb);
	i2400m->ack_skb = ERR_PTR(code);
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
}