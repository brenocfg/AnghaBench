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
struct st_data_s {int /*<<< orphan*/  lock; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_waitq; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  st_ll_sleep_state (struct st_data_s*,unsigned long) ; 
 int /*<<< orphan*/  st_tx_wakeup (struct st_data_s*) ; 

__attribute__((used)) static inline void st_wakeup_ack(struct st_data_s *st_gdata,
	unsigned char cmd)
{
	struct sk_buff *waiting_skb;
	unsigned long flags = 0;

	spin_lock_irqsave(&st_gdata->lock, flags);
	/* de-Q from waitQ and Q in txQ now that the
	 * chip is awake
	 */
	while ((waiting_skb = skb_dequeue(&st_gdata->tx_waitq)))
		skb_queue_tail(&st_gdata->txq, waiting_skb);

	/* state forwarded to ST LL */
	st_ll_sleep_state(st_gdata, (unsigned long)cmd);
	spin_unlock_irqrestore(&st_gdata->lock, flags);

	/* wake up to send the recently copied skbs from waitQ */
	st_tx_wakeup(st_gdata);
}