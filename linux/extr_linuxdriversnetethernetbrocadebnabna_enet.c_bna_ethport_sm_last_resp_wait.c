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
struct bna_ethport {int dummy; } ;
typedef  enum bna_ethport_event { ____Placeholder_bna_ethport_event } bna_ethport_event ;

/* Variables and functions */
#define  ETHPORT_E_DOWN 132 
#define  ETHPORT_E_FAIL 131 
#define  ETHPORT_E_FWRESP_DOWN 130 
#define  ETHPORT_E_FWRESP_UP_FAIL 129 
#define  ETHPORT_E_FWRESP_UP_OK 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_bfi_ethport_down (struct bna_ethport*) ; 
 int /*<<< orphan*/  bna_ethport_sm_stopped ; 

__attribute__((used)) static void
bna_ethport_sm_last_resp_wait(struct bna_ethport *ethport,
			enum bna_ethport_event event)
{
	switch (event) {
	case ETHPORT_E_FAIL:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		break;

	case ETHPORT_E_DOWN:
		/**
		 * This event is received due to Rx objects stopping in
		 * parallel to ethport
		 */
		/* No-op */
		break;

	case ETHPORT_E_FWRESP_UP_OK:
		/* up_resp_wait->last_resp_wait transition on ETHPORT_T_STOP */
		bna_bfi_ethport_down(ethport);
		break;

	case ETHPORT_E_FWRESP_UP_FAIL:
	case ETHPORT_E_FWRESP_DOWN:
		bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
		break;

	default:
		bfa_sm_fault(event);
	}
}