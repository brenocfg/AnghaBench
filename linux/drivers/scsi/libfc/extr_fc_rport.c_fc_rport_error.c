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
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  flags; int /*<<< orphan*/  retries; int /*<<< orphan*/  rp_mutex; struct fc_lport* local_port; } ;
struct fc_lport {int /*<<< orphan*/  point_to_multipoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_RP_STARTED ; 
 int /*<<< orphan*/  RPORT_EV_FAILED ; 
#define  RPORT_ST_ADISC 136 
#define  RPORT_ST_DELETE 135 
#define  RPORT_ST_FLOGI 134 
#define  RPORT_ST_INIT 133 
#define  RPORT_ST_PLOGI 132 
#define  RPORT_ST_PLOGI_WAIT 131 
#define  RPORT_ST_PRLI 130 
#define  RPORT_ST_READY 129 
#define  RPORT_ST_RTV 128 
 int /*<<< orphan*/  fc_rport_enter_delete (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_enter_logo (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_enter_ready (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_rport_error(struct fc_rport_priv *rdata, int err)
{
	struct fc_lport *lport = rdata->local_port;

	lockdep_assert_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Error %d in state %s, retries %d\n",
		     -err, fc_rport_state(rdata), rdata->retries);

	switch (rdata->rp_state) {
	case RPORT_ST_FLOGI:
		rdata->flags &= ~FC_RP_STARTED;
		fc_rport_enter_delete(rdata, RPORT_EV_FAILED);
		break;
	case RPORT_ST_PLOGI:
		if (lport->point_to_multipoint) {
			rdata->flags &= ~FC_RP_STARTED;
			fc_rport_enter_delete(rdata, RPORT_EV_FAILED);
		} else
			fc_rport_enter_logo(rdata);
		break;
	case RPORT_ST_RTV:
		fc_rport_enter_ready(rdata);
		break;
	case RPORT_ST_PRLI:
	case RPORT_ST_ADISC:
		fc_rport_enter_logo(rdata);
		break;
	case RPORT_ST_PLOGI_WAIT:
	case RPORT_ST_DELETE:
	case RPORT_ST_READY:
	case RPORT_ST_INIT:
		break;
	}
}