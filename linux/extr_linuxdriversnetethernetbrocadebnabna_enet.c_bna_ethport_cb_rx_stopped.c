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
struct bna_ethport {scalar_t__ rx_started_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ETHPORT_F_RX_STARTED ; 
 int /*<<< orphan*/  ETHPORT_E_DOWN ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int ethport_is_up (struct bna_ethport*) ; 

void
bna_ethport_cb_rx_stopped(struct bna_ethport *ethport)
{
	int ethport_up = ethport_is_up(ethport);

	ethport->rx_started_count--;

	if (ethport->rx_started_count == 0) {
		ethport->flags &= ~BNA_ETHPORT_F_RX_STARTED;

		if (ethport_up)
			bfa_fsm_send_event(ethport, ETHPORT_E_DOWN);
	}
}