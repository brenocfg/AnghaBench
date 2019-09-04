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
struct bna_enet {void (* stop_cbfn ) (void*) ;void* stop_cbarg; int /*<<< orphan*/  flags; TYPE_1__* bna; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_2__ {void* bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ENET_F_ENABLED ; 
 int BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  ENET_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_enet*,int /*<<< orphan*/ ) ; 
 void stub1 (void*) ; 

void
bna_enet_disable(struct bna_enet *enet, enum bna_cleanup_type type,
		 void (*cbfn)(void *))
{
	if (type == BNA_SOFT_CLEANUP) {
		(*cbfn)(enet->bna->bnad);
		return;
	}

	enet->stop_cbfn = cbfn;
	enet->stop_cbarg = enet->bna->bnad;

	enet->flags &= ~BNA_ENET_F_ENABLED;

	bfa_fsm_send_event(enet, ENET_E_STOP);
}