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
struct TYPE_3__ {int /*<<< orphan*/  reap_task; int /*<<< orphan*/  reap_list; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; TYPE_1__ cm; int /*<<< orphan*/  wq; } ;
struct ipoib_cm_tx {TYPE_2__* neigh; int /*<<< orphan*/  list; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,scalar_t__) ; 
 struct ipoib_dev_priv* ipoib_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ipoib_cm_destroy_tx(struct ipoib_cm_tx *tx)
{
	struct ipoib_dev_priv *priv = ipoib_priv(tx->dev);
	unsigned long flags;
	if (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) {
		spin_lock_irqsave(&priv->lock, flags);
		list_move(&tx->list, &priv->cm.reap_list);
		queue_work(priv->wq, &priv->cm.reap_task);
		ipoib_dbg(priv, "Reap connection for gid %pI6\n",
			  tx->neigh->daddr + 4);
		tx->neigh = NULL;
		spin_unlock_irqrestore(&priv->lock, flags);
	}
}