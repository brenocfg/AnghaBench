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
struct bna_ethport {scalar_t__ link_status; TYPE_1__* bna; int /*<<< orphan*/  (* link_cbfn ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ETHPORT_F_PORT_ENABLED ; 
 scalar_t__ BNA_LINK_DOWN ; 
 int /*<<< orphan*/  ETHPORT_E_FAIL ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bna_ethport_fail(struct bna_ethport *ethport)
{
	/* Reset the physical port status to enabled */
	ethport->flags |= BNA_ETHPORT_F_PORT_ENABLED;

	if (ethport->link_status != BNA_LINK_DOWN) {
		ethport->link_status = BNA_LINK_DOWN;
		ethport->link_cbfn(ethport->bna->bnad, BNA_LINK_DOWN);
	}
	bfa_fsm_send_event(ethport, ETHPORT_E_FAIL);
}