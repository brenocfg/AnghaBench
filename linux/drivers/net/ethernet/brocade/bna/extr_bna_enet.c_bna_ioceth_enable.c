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
struct bna_ioceth {scalar_t__ fsm; TYPE_1__* bna; } ;
typedef  scalar_t__ bfa_fsm_t ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCETH_E_ENABLE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ioceth*,int /*<<< orphan*/ ) ; 
 scalar_t__ bna_ioceth_sm_ready ; 
 scalar_t__ bna_ioceth_sm_stopped ; 
 int /*<<< orphan*/  bnad_cb_ioceth_ready (int /*<<< orphan*/ ) ; 

void
bna_ioceth_enable(struct bna_ioceth *ioceth)
{
	if (ioceth->fsm == (bfa_fsm_t)bna_ioceth_sm_ready) {
		bnad_cb_ioceth_ready(ioceth->bna->bnad);
		return;
	}

	if (ioceth->fsm == (bfa_fsm_t)bna_ioceth_sm_stopped)
		bfa_fsm_send_event(ioceth, IOCETH_E_ENABLE);
}