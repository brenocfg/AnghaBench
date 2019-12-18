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
struct bna_enet {scalar_t__ fsm; int flags; } ;
typedef  scalar_t__ bfa_sm_t ;

/* Variables and functions */
 int BNA_ENET_F_ENABLED ; 
 int BNA_ENET_F_IOCETH_READY ; 
 int /*<<< orphan*/  ENET_E_START ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_enet*,int /*<<< orphan*/ ) ; 
 scalar_t__ bna_enet_sm_stopped ; 

void
bna_enet_enable(struct bna_enet *enet)
{
	if (enet->fsm != (bfa_sm_t)bna_enet_sm_stopped)
		return;

	enet->flags |= BNA_ENET_F_ENABLED;

	if (enet->flags & BNA_ENET_F_IOCETH_READY)
		bfa_fsm_send_event(enet, ENET_E_START);
}