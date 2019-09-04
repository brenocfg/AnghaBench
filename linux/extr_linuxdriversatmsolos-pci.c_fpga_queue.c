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
struct solos_card {int tx_mask; int /*<<< orphan*/  tx_queue_lock; int /*<<< orphan*/ * tx_queue; } ;
struct sk_buff {int dummy; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_2__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 TYPE_1__* SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  fpga_tx (struct solos_card*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fpga_queue(struct solos_card *card, int port, struct sk_buff *skb,
		       struct atm_vcc *vcc)
{
	int old_len;
	unsigned long flags;

	SKB_CB(skb)->vcc = vcc;

	spin_lock_irqsave(&card->tx_queue_lock, flags);
	old_len = skb_queue_len(&card->tx_queue[port]);
	skb_queue_tail(&card->tx_queue[port], skb);
	if (!old_len)
		card->tx_mask |= (1 << port);
	spin_unlock_irqrestore(&card->tx_queue_lock, flags);

	/* Theoretically we could just schedule the tasklet here, but
	   that introduces latency we don't want -- it's noticeable */
	if (!old_len)
		fpga_tx(card);
}