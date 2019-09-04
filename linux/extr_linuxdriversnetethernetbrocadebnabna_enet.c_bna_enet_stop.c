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
struct bna_enet {int /*<<< orphan*/  flags; TYPE_1__* bna; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/  stop_cbfn; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioceth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ENET_F_IOCETH_READY ; 
 int /*<<< orphan*/  ENET_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_enet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ioceth_cb_enet_stopped ; 

__attribute__((used)) static void
bna_enet_stop(struct bna_enet *enet)
{
	enet->stop_cbfn = bna_ioceth_cb_enet_stopped;
	enet->stop_cbarg = &enet->bna->ioceth;

	enet->flags &= ~BNA_ENET_F_IOCETH_READY;
	bfa_fsm_send_event(enet, ENET_E_STOP);
}