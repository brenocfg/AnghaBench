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
typedef  size_t u32 ;
struct tcp_ack_filter {size_t pending_base; size_t pending_acks_idx; scalar_t__ tcp_session; TYPE_2__* pending_acks; TYPE_1__* ack_session_info; } ;
struct wilc_vif {struct tcp_ack_filter ack_filter; struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  txq_event; int /*<<< orphan*/  txq_spinlock; } ;
struct txq_entry_t {int status; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* tx_complete_func ) (int /*<<< orphan*/ ,int) ;} ;
struct net_device {int dummy; } ;
struct TYPE_4__ {size_t session_index; size_t ack_num; struct txq_entry_t* txqe; } ;
struct TYPE_3__ {size_t bigger_ack_num; } ;

/* Variables and functions */
 size_t MAX_PENDING_ACKS ; 
 int MAX_TCP_SESSION ; 
 int /*<<< orphan*/  kfree (struct txq_entry_t*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wlan_txq_remove (struct wilc*,struct txq_entry_t*) ; 

__attribute__((used)) static void wilc_wlan_txq_filter_dup_tcp_ack(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;
	struct tcp_ack_filter *f = &vif->ack_filter;
	u32 i = 0;
	u32 dropped = 0;
	unsigned long flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);
	for (i = f->pending_base;
	     i < (f->pending_base + f->pending_acks_idx); i++) {
		u32 index;
		u32 bigger_ack_num;

		if (i >= MAX_PENDING_ACKS)
			break;

		index = f->pending_acks[i].session_index;

		if (index >= 2 * MAX_TCP_SESSION)
			break;

		bigger_ack_num = f->ack_session_info[index].bigger_ack_num;

		if (f->pending_acks[i].ack_num < bigger_ack_num) {
			struct txq_entry_t *tqe;

			tqe = f->pending_acks[i].txqe;
			if (tqe) {
				wilc_wlan_txq_remove(wilc, tqe);
				tqe->status = 1;
				if (tqe->tx_complete_func)
					tqe->tx_complete_func(tqe->priv,
							      tqe->status);
				kfree(tqe);
				dropped++;
			}
		}
	}
	f->pending_acks_idx = 0;
	f->tcp_session = 0;

	if (f->pending_base == 0)
		f->pending_base = MAX_TCP_SESSION;
	else
		f->pending_base = 0;

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	while (dropped > 0) {
		wait_for_completion_timeout(&wilc->txq_event,
					    msecs_to_jiffies(1));
		dropped--;
	}
}