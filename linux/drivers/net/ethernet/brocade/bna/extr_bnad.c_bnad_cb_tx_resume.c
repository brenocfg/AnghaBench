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
typedef  int /*<<< orphan*/  u32 ;
struct bnad_tx_info {struct bna_tcb** tcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  enet; } ;
struct bnad {int /*<<< orphan*/  perm_addr; TYPE_1__ bna; int /*<<< orphan*/  netdev; } ;
struct bna_tx {scalar_t__ priv; } ;
struct bna_tcb {scalar_t__* hw_consumer_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BNAD_MAX_TXQ_PER_TX ; 
 int /*<<< orphan*/  BNAD_TXQ_TX_STARTED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bna_enet_perm_mac_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_set_netdev_perm_addr (struct bnad*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_queue_wakeup ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_cb_tx_resume(struct bnad *bnad, struct bna_tx *tx)
{
	struct bnad_tx_info *tx_info = (struct bnad_tx_info *)tx->priv;
	struct bna_tcb *tcb;
	u32 txq_id;
	int i;

	for (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) {
		tcb = tx_info->tcb[i];
		if (!tcb)
			continue;
		txq_id = tcb->id;

		BUG_ON(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags));
		set_bit(BNAD_TXQ_TX_STARTED, &tcb->flags);
		BUG_ON(*(tcb->hw_consumer_index) != 0);

		if (netif_carrier_ok(bnad->netdev)) {
			netif_wake_subqueue(bnad->netdev, txq_id);
			BNAD_UPDATE_CTR(bnad, netif_queue_wakeup);
		}
	}

	/*
	 * Workaround for first ioceth enable failure & we
	 * get a 0 MAC address. We try to get the MAC address
	 * again here.
	 */
	if (is_zero_ether_addr(bnad->perm_addr)) {
		bna_enet_perm_mac_get(&bnad->bna.enet, bnad->perm_addr);
		bnad_set_netdev_perm_addr(bnad);
	}
}