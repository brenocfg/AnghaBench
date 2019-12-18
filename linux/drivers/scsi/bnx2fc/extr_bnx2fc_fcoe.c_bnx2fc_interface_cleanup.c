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
struct fcoe_port {int /*<<< orphan*/  timer; } ;
struct fcoe_ctlr {struct fc_lport* lp; } ;
struct fc_lport {int dummy; } ;
struct bnx2fc_interface {struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_free_vport (struct bnx2fc_hba*,struct fc_lport*) ; 
 int /*<<< orphan*/  bnx2fc_net_cleanup (struct bnx2fc_interface*) ; 
 struct fcoe_ctlr* bnx2fc_to_ctlr (struct bnx2fc_interface*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_clean_pending_queue (struct fc_lport*) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 

__attribute__((used)) static void bnx2fc_interface_cleanup(struct bnx2fc_interface *interface)
{
	struct fcoe_ctlr *ctlr = bnx2fc_to_ctlr(interface);
	struct fc_lport *lport = ctlr->lp;
	struct fcoe_port *port = lport_priv(lport);
	struct bnx2fc_hba *hba = interface->hba;

	/* Stop the transmit retry timer */
	del_timer_sync(&port->timer);

	/* Free existing transmit skbs */
	fcoe_clean_pending_queue(lport);

	bnx2fc_net_cleanup(interface);

	bnx2fc_free_vport(hba, lport);
}