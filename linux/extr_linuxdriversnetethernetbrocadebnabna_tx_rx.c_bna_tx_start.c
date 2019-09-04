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
struct bna_tx {int flags; } ;

/* Variables and functions */
 int BNA_TX_F_ENABLED ; 
 int BNA_TX_F_ENET_STARTED ; 
 int /*<<< orphan*/  TX_E_START ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_tx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_tx_start(struct bna_tx *tx)
{
	tx->flags |= BNA_TX_F_ENET_STARTED;
	if (tx->flags & BNA_TX_F_ENABLED)
		bfa_fsm_send_event(tx, TX_E_START);
}