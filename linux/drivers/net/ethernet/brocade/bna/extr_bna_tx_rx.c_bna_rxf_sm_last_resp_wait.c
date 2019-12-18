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
struct bna_rxf {int dummy; } ;
typedef  enum bna_rxf_event { ____Placeholder_bna_rxf_event } bna_rxf_event ;

/* Variables and functions */
#define  RXF_E_FAIL 129 
#define  RXF_E_FW_RESP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_rxf_cfg_reset (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_sm_stopped ; 

__attribute__((used)) static void
bna_rxf_sm_last_resp_wait(struct bna_rxf *rxf, enum bna_rxf_event event)
{
	switch (event) {
	case RXF_E_FAIL:
	case RXF_E_FW_RESP:
		bna_rxf_cfg_reset(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		break;

	default:
		bfa_sm_fault(event);
	}
}