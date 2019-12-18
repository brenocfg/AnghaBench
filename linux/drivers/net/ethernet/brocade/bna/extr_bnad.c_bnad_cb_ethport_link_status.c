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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u32 ;
struct bnad {size_t num_tx; size_t num_txq_per_tx; int /*<<< orphan*/  netdev; TYPE_1__* tx_info; int /*<<< orphan*/  run_flags; } ;
struct bna_tcb {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
typedef  enum bna_link_status { ____Placeholder_bna_link_status } bna_link_status ;
struct TYPE_2__ {struct bna_tcb** tcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_CEE_RUNNING ; 
 int /*<<< orphan*/  BNAD_TXQ_TX_STARTED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int BNA_CEE_UP ; 
 int BNA_LINK_UP ; 
 int /*<<< orphan*/  cee_toggle ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_toggle ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_queue_stop ; 
 int /*<<< orphan*/  netif_queue_wakeup ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bnad_cb_ethport_link_status(struct bnad *bnad,
			enum bna_link_status link_status)
{
	bool link_up = false;

	link_up = (link_status == BNA_LINK_UP) || (link_status == BNA_CEE_UP);

	if (link_status == BNA_CEE_UP) {
		if (!test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags))
			BNAD_UPDATE_CTR(bnad, cee_toggle);
		set_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags);
	} else {
		if (test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags))
			BNAD_UPDATE_CTR(bnad, cee_toggle);
		clear_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags);
	}

	if (link_up) {
		if (!netif_carrier_ok(bnad->netdev)) {
			uint tx_id, tcb_id;
			netdev_info(bnad->netdev, "link up\n");
			netif_carrier_on(bnad->netdev);
			BNAD_UPDATE_CTR(bnad, link_toggle);
			for (tx_id = 0; tx_id < bnad->num_tx; tx_id++) {
				for (tcb_id = 0; tcb_id < bnad->num_txq_per_tx;
				      tcb_id++) {
					struct bna_tcb *tcb =
					bnad->tx_info[tx_id].tcb[tcb_id];
					u32 txq_id;
					if (!tcb)
						continue;

					txq_id = tcb->id;

					if (test_bit(BNAD_TXQ_TX_STARTED,
						     &tcb->flags)) {
						/*
						 * Force an immediate
						 * Transmit Schedule */
						netif_wake_subqueue(
								bnad->netdev,
								txq_id);
						BNAD_UPDATE_CTR(bnad,
							netif_queue_wakeup);
					} else {
						netif_stop_subqueue(
								bnad->netdev,
								txq_id);
						BNAD_UPDATE_CTR(bnad,
							netif_queue_stop);
					}
				}
			}
		}
	} else {
		if (netif_carrier_ok(bnad->netdev)) {
			netdev_info(bnad->netdev, "link down\n");
			netif_carrier_off(bnad->netdev);
			BNAD_UPDATE_CTR(bnad, link_toggle);
		}
	}
}