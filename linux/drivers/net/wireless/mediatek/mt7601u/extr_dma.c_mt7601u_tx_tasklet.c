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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct mt7601u_dev {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_skb_done; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  stat_wq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_MORE_STATS ; 
 int /*<<< orphan*/  MT7601U_STATE_READING_STATS ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mt7601u_tx_status (struct mt7601u_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (int /*<<< orphan*/ *,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt7601u_tx_tasklet(unsigned long data)
{
	struct mt7601u_dev *dev = (struct mt7601u_dev *) data;
	struct sk_buff_head skbs;
	unsigned long flags;

	__skb_queue_head_init(&skbs);

	spin_lock_irqsave(&dev->tx_lock, flags);

	set_bit(MT7601U_STATE_MORE_STATS, &dev->state);
	if (!test_and_set_bit(MT7601U_STATE_READING_STATS, &dev->state))
		queue_delayed_work(dev->stat_wq, &dev->stat_work,
				   msecs_to_jiffies(10));

	skb_queue_splice_init(&dev->tx_skb_done, &skbs);

	spin_unlock_irqrestore(&dev->tx_lock, flags);

	while (!skb_queue_empty(&skbs)) {
		struct sk_buff *skb = __skb_dequeue(&skbs);

		mt7601u_tx_status(dev, skb);
	}
}