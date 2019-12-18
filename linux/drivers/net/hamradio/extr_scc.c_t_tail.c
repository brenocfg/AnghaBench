#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ tx_state; } ;
struct TYPE_3__ {int mintime; } ;
struct scc_channel {int /*<<< orphan*/  dev; TYPE_2__ stat; TYPE_1__ kiss; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_wdog; } ;

/* Variables and functions */
 scalar_t__ TXS_IDLE ; 
 scalar_t__ TXS_TIMEOUT ; 
 scalar_t__ TXS_WAIT ; 
 int /*<<< orphan*/  TX_OFF ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct scc_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 struct scc_channel* scc ; 
 int /*<<< orphan*/  scc_key_trx (struct scc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_start_tx_timer (struct scc_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  t_dwait ; 
 int /*<<< orphan*/  tx_t ; 

__attribute__((used)) static void t_tail(struct timer_list *t)
{
	struct scc_channel *scc = from_timer(scc, t, tx_t);
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags); 
 	del_timer(&scc->tx_wdog);	
 	scc_key_trx(scc, TX_OFF);
	spin_unlock_irqrestore(&scc->lock, flags);

 	if (scc->stat.tx_state == TXS_TIMEOUT)		/* we had a timeout? */
 	{
 		scc->stat.tx_state = TXS_WAIT;
		scc_start_tx_timer(scc, t_dwait, scc->kiss.mintime*100);
 		return;
 	}
 	
 	scc->stat.tx_state = TXS_IDLE;
	netif_wake_queue(scc->dev);
}