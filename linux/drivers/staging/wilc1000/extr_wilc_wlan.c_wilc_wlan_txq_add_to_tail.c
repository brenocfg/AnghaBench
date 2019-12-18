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
struct wilc_vif {struct wilc* wilc; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct wilc {int txq_entries; int /*<<< orphan*/  txq_event; int /*<<< orphan*/  txq_spinlock; TYPE_1__ txq_head; } ;
struct txq_entry_t {int /*<<< orphan*/  list; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void wilc_wlan_txq_add_to_tail(struct net_device *dev,
				      struct txq_entry_t *tqe)
{
	unsigned long flags;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	list_add_tail(&tqe->list, &wilc->txq_head.list);
	wilc->txq_entries += 1;

	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	complete(&wilc->txq_event);
}