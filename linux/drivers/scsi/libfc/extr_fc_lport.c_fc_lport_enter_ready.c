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
struct TYPE_2__ {int /*<<< orphan*/  (* disc_start ) (int /*<<< orphan*/ ,struct fc_lport*) ;} ;
struct fc_lport {TYPE_1__ tt; int /*<<< orphan*/  ptp_rdata; scalar_t__ vport; int /*<<< orphan*/  lp_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_VPORT_ACTIVE ; 
 int /*<<< orphan*/  LPORT_ST_READY ; 
 int /*<<< orphan*/  fc_lport_disc_callback ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_vport_set_state (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_vports_linkchange (struct fc_lport*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct fc_lport*) ; 

__attribute__((used)) static void fc_lport_enter_ready(struct fc_lport *lport)
{
	lockdep_assert_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered READY from state %s\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_READY);
	if (lport->vport)
		fc_vport_set_state(lport->vport, FC_VPORT_ACTIVE);
	fc_vports_linkchange(lport);

	if (!lport->ptp_rdata)
		lport->tt.disc_start(fc_lport_disc_callback, lport);
}