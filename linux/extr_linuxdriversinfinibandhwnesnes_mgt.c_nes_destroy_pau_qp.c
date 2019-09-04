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
struct nes_qp {int /*<<< orphan*/  pau_lock; int /*<<< orphan*/  cm_node; int /*<<< orphan*/  pau_list; } ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_mgt_free_skb (struct nes_device*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_rem_ref_cm_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pau_qps_destroyed ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void nes_destroy_pau_qp(struct nes_device *nesdev, struct nes_qp *nesqp)
{
	struct sk_buff *skb;
	unsigned long flags;
	atomic_inc(&pau_qps_destroyed);

	/* Free packets that have not yet been forwarded */
	/* Lock is acquired by skb_dequeue when removing the skb */
	spin_lock_irqsave(&nesqp->pau_lock, flags);
	while (skb_queue_len(&nesqp->pau_list)) {
		skb = skb_dequeue(&nesqp->pau_list);
		nes_mgt_free_skb(nesdev, skb, PCI_DMA_TODEVICE);
		nes_rem_ref_cm_node(nesqp->cm_node);
	}
	spin_unlock_irqrestore(&nesqp->pau_lock, flags);
}