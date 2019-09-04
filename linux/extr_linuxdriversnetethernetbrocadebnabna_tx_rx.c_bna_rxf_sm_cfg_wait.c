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
#define  RXF_E_CONFIG 131 
#define  RXF_E_FAIL 130 
#define  RXF_E_FW_RESP 129 
#define  RXF_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_rxf_cfg_apply (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_cfg_reset (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_sm_last_resp_wait ; 
 int /*<<< orphan*/  bna_rxf_sm_started ; 
 int /*<<< orphan*/  bna_rxf_sm_stopped ; 
 int /*<<< orphan*/  call_rxf_cam_fltr_cbfn (struct bna_rxf*) ; 
 int /*<<< orphan*/  call_rxf_start_cbfn (struct bna_rxf*) ; 

__attribute__((used)) static void
bna_rxf_sm_cfg_wait(struct bna_rxf *rxf, enum bna_rxf_event event)
{
	switch (event) {
	case RXF_E_STOP:
		bfa_fsm_set_state(rxf, bna_rxf_sm_last_resp_wait);
		break;

	case RXF_E_FAIL:
		bna_rxf_cfg_reset(rxf);
		call_rxf_start_cbfn(rxf);
		call_rxf_cam_fltr_cbfn(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		break;

	case RXF_E_CONFIG:
		/* No-op */
		break;

	case RXF_E_FW_RESP:
		if (!bna_rxf_cfg_apply(rxf)) {
			/* No more pending config updates */
			bfa_fsm_set_state(rxf, bna_rxf_sm_started);
		}
		break;

	default:
		bfa_sm_fault(event);
	}
}