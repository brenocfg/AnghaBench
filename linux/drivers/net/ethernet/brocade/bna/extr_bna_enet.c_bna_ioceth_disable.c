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
struct bna_ioceth {TYPE_1__* bna; int /*<<< orphan*/  stop_cbarg; int /*<<< orphan*/  (* stop_cbfn ) (int /*<<< orphan*/ ) ;} ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  IOCETH_E_DISABLE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ioceth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_ioceth_disabled (int /*<<< orphan*/ ) ; 

void
bna_ioceth_disable(struct bna_ioceth *ioceth, enum bna_cleanup_type type)
{
	if (type == BNA_SOFT_CLEANUP) {
		bnad_cb_ioceth_disabled(ioceth->bna->bnad);
		return;
	}

	ioceth->stop_cbfn = bnad_cb_ioceth_disabled;
	ioceth->stop_cbarg = ioceth->bna->bnad;

	bfa_fsm_send_event(ioceth, IOCETH_E_DISABLE);
}