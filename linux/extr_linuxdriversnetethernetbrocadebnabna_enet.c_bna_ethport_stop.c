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
struct bna_ethport {int /*<<< orphan*/  stop_cbfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHPORT_E_STOP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_enet_cb_ethport_stopped ; 

__attribute__((used)) static void
bna_ethport_stop(struct bna_ethport *ethport)
{
	ethport->stop_cbfn = bna_enet_cb_ethport_stopped;
	bfa_fsm_send_event(ethport, ETHPORT_E_STOP);
}