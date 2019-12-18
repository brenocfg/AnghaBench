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
struct bna_tx {int dummy; } ;
typedef  enum bna_tx_event { ____Placeholder_bna_tx_event } bna_tx_event ;

/* Variables and functions */
#define  TX_E_BW_UPDATE 130 
#define  TX_E_CLEANUP_DONE 129 
#define  TX_E_FAIL 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_tx_sm_stopped ; 

__attribute__((used)) static void
bna_tx_sm_cleanup_wait(struct bna_tx *tx, enum bna_tx_event event)
{
	switch (event) {
	case TX_E_FAIL:
	case TX_E_BW_UPDATE:
		/* No-op */
		break;

	case TX_E_CLEANUP_DONE:
		bfa_fsm_set_state(tx, bna_tx_sm_stopped);
		break;

	default:
		bfa_sm_fault(event);
	}
}