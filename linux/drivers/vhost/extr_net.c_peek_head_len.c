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
struct vhost_net_virtqueue {scalar_t__ rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_1__ sk_receive_queue; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct sk_buff* skb_peek (TYPE_1__*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vhost_net_buf_peek (struct vhost_net_virtqueue*) ; 

__attribute__((used)) static int peek_head_len(struct vhost_net_virtqueue *rvq, struct sock *sk)
{
	struct sk_buff *head;
	int len = 0;
	unsigned long flags;

	if (rvq->rx_ring)
		return vhost_net_buf_peek(rvq);

	spin_lock_irqsave(&sk->sk_receive_queue.lock, flags);
	head = skb_peek(&sk->sk_receive_queue);
	if (likely(head)) {
		len = head->len;
		if (skb_vlan_tag_present(head))
			len += VLAN_HLEN;
	}

	spin_unlock_irqrestore(&sk->sk_receive_queue.lock, flags);
	return len;
}