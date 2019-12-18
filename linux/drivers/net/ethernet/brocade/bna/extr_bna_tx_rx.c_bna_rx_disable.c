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
struct bna_rx {void (* stop_cbfn ) (void*,struct bna_rx*) ;void* stop_cbarg; int /*<<< orphan*/  rx_flags; TYPE_1__* bna; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_2__ {void* bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_RX_F_ENABLED ; 
 int BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  RX_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rx*,int /*<<< orphan*/ ) ; 
 void stub1 (void*,struct bna_rx*) ; 

void
bna_rx_disable(struct bna_rx *rx, enum bna_cleanup_type type,
		void (*cbfn)(void *, struct bna_rx *))
{
	if (type == BNA_SOFT_CLEANUP) {
		/* h/w should not be accessed. Treat we're stopped */
		(*cbfn)(rx->bna->bnad, rx);
	} else {
		rx->stop_cbfn = cbfn;
		rx->stop_cbarg = rx->bna->bnad;

		rx->rx_flags &= ~BNA_RX_F_ENABLED;

		bfa_fsm_send_event(rx, RX_E_STOP);
	}
}