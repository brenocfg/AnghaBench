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
struct bna_tx {int /*<<< orphan*/  flags; TYPE_1__* bna; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/  stop_cbfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_TX_F_ENET_STARTED ; 
 int /*<<< orphan*/  TX_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_tx_mod_cb_tx_stopped ; 

__attribute__((used)) static void
bna_tx_stop(struct bna_tx *tx)
{
	tx->stop_cbfn = bna_tx_mod_cb_tx_stopped;
	tx->stop_cbarg = &tx->bna->tx_mod;

	tx->flags &= ~BNA_TX_F_ENET_STARTED;
	bfa_fsm_send_event(tx, TX_E_STOP);
}