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
struct fcoe_rport {int dummy; } ;
struct fcoe_ctlr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * disc_stop_final; int /*<<< orphan*/ * disc_stop; int /*<<< orphan*/ * disc_start; int /*<<< orphan*/ * disc_recv_req; } ;
struct fc_lport {scalar_t__ state; int rport_priv_size; int point_to_multipoint; TYPE_1__ tt; } ;
typedef  enum fip_mode { ____Placeholder_fip_mode } fip_mode ;

/* Variables and functions */
 int FIP_MODE_VN2VN ; 
 scalar_t__ LPORT_ST_DISABLED ; 
 scalar_t__ LPORT_ST_RESET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fc_disc_config (struct fc_lport*,void*) ; 
 int /*<<< orphan*/ * fcoe_ctlr_disc_recv ; 
 int /*<<< orphan*/ * fcoe_ctlr_disc_start ; 
 int /*<<< orphan*/ * fcoe_ctlr_disc_stop ; 
 int /*<<< orphan*/ * fcoe_ctlr_disc_stop_final ; 

__attribute__((used)) static void fcoe_ctlr_mode_set(struct fc_lport *lport, struct fcoe_ctlr *fip,
			       enum fip_mode fip_mode)
{
	void *priv;

	WARN_ON(lport->state != LPORT_ST_RESET &&
		lport->state != LPORT_ST_DISABLED);

	if (fip_mode == FIP_MODE_VN2VN) {
		lport->rport_priv_size = sizeof(struct fcoe_rport);
		lport->point_to_multipoint = 1;
		lport->tt.disc_recv_req = fcoe_ctlr_disc_recv;
		lport->tt.disc_start = fcoe_ctlr_disc_start;
		lport->tt.disc_stop = fcoe_ctlr_disc_stop;
		lport->tt.disc_stop_final = fcoe_ctlr_disc_stop_final;
		priv = fip;
	} else {
		lport->rport_priv_size = 0;
		lport->point_to_multipoint = 0;
		lport->tt.disc_recv_req = NULL;
		lport->tt.disc_start = NULL;
		lport->tt.disc_stop = NULL;
		lport->tt.disc_stop_final = NULL;
		priv = lport;
	}

	fc_disc_config(lport, priv);
}