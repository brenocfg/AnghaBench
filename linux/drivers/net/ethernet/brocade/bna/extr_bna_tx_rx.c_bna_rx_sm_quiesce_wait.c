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
struct bna_rx {int dummy; } ;
typedef  enum bna_rx_event { ____Placeholder_bna_rx_event } bna_rx_event ;

/* Variables and functions */
#define  RX_E_CLEANUP_DONE 130 
#define  RX_E_FAIL 129 
#define  RX_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_rx_sm_cleanup_wait ; 
 int /*<<< orphan*/  bna_rx_sm_failed ; 
 int /*<<< orphan*/  bna_rx_sm_start_wait ; 

__attribute__((used)) static void
bna_rx_sm_quiesce_wait(struct bna_rx *rx, enum bna_rx_event event)
{
	switch (event) {
	case RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_wait);
		break;

	case RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_failed);
		break;

	case RX_E_CLEANUP_DONE:
		bfa_fsm_set_state(rx, bna_rx_sm_start_wait);
		break;

	default:
		bfa_sm_fault(event);
		break;
	}
}