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
struct bna_ioceth {int /*<<< orphan*/  ioc; } ;
typedef  enum bna_ioceth_event { ____Placeholder_bna_ioceth_event } bna_ioceth_event ;

/* Variables and functions */
#define  IOCETH_E_DISABLE 130 
#define  IOCETH_E_IOC_FAILED 129 
#define  IOCETH_E_IOC_RESET 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_ioceth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_ioceth_sm_ioc_disable_wait ; 
 int /*<<< orphan*/  bna_ioceth_sm_ioc_ready_wait ; 
 int /*<<< orphan*/  enable_mbox_intr (struct bna_ioceth*) ; 

__attribute__((used)) static void
bna_ioceth_sm_failed(struct bna_ioceth *ioceth,
			enum bna_ioceth_event event)
{
	switch (event) {
	case IOCETH_E_DISABLE:
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_disable_wait);
		bfa_nw_ioc_disable(&ioceth->ioc);
		break;

	case IOCETH_E_IOC_RESET:
		enable_mbox_intr(ioceth);
		bfa_fsm_set_state(ioceth, bna_ioceth_sm_ioc_ready_wait);
		break;

	case IOCETH_E_IOC_FAILED:
		break;

	default:
		bfa_sm_fault(event);
	}
}