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
struct bna_enet {int /*<<< orphan*/ * mtu_cbfn; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/ * stop_cbfn; int /*<<< orphan*/  type; scalar_t__ mtu; scalar_t__ flags; struct bna* bna; } ;
struct bna {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ENET_T_REGULAR ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_enet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_enet_sm_stopped ; 

__attribute__((used)) static void
bna_enet_init(struct bna_enet *enet, struct bna *bna)
{
	enet->bna = bna;
	enet->flags = 0;
	enet->mtu = 0;
	enet->type = BNA_ENET_T_REGULAR;

	enet->stop_cbfn = NULL;
	enet->stop_cbarg = NULL;

	enet->mtu_cbfn = NULL;

	bfa_fsm_set_state(enet, bna_enet_sm_stopped);
}