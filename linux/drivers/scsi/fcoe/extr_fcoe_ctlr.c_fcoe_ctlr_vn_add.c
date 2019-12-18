#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ port_id; int port_name; int node_name; } ;
struct TYPE_6__ {TYPE_2__ ids; } ;
struct fcoe_rport {scalar_t__ time; int /*<<< orphan*/  vn_mac; int /*<<< orphan*/  enode_mac; int /*<<< orphan*/  login_count; int /*<<< orphan*/  flags; scalar_t__ fcoe_len; TYPE_3__ rdata; } ;
struct fcoe_ctlr {scalar_t__ port_id; struct fc_lport* lp; } ;
struct fc_rport_identifiers {int port_name; int node_name; } ;
struct fc_rport_priv {int /*<<< orphan*/  rp_state; int /*<<< orphan*/  rp_mutex; struct fc_rport_identifiers ids; int /*<<< orphan*/  disc_id; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  disc_id; int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,scalar_t__,...) ; 
 struct fc_rport_priv* fc_rport_create (struct fc_lport*,scalar_t__) ; 
 int /*<<< orphan*/  fc_rport_logoff (struct fc_rport_priv*) ; 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_rport_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fcoe_ctlr_vn_add(struct fcoe_ctlr *fip, struct fcoe_rport *new)
{
	struct fc_lport *lport = fip->lp;
	struct fc_rport_priv *rdata;
	struct fc_rport_identifiers *ids;
	struct fcoe_rport *frport;
	u32 port_id;

	port_id = new->rdata.ids.port_id;
	if (port_id == fip->port_id)
		return;

	mutex_lock(&lport->disc.disc_mutex);
	rdata = fc_rport_create(lport, port_id);
	if (!rdata) {
		mutex_unlock(&lport->disc.disc_mutex);
		return;
	}
	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&lport->disc.disc_mutex);

	rdata->ops = &fcoe_ctlr_vn_rport_ops;
	rdata->disc_id = lport->disc.disc_id;

	ids = &rdata->ids;
	if ((ids->port_name != -1 &&
	     ids->port_name != new->rdata.ids.port_name) ||
	    (ids->node_name != -1 &&
	     ids->node_name != new->rdata.ids.node_name)) {
		mutex_unlock(&rdata->rp_mutex);
		LIBFCOE_FIP_DBG(fip, "vn_add rport logoff %6.6x\n", port_id);
		fc_rport_logoff(rdata);
		mutex_lock(&rdata->rp_mutex);
	}
	ids->port_name = new->rdata.ids.port_name;
	ids->node_name = new->rdata.ids.node_name;
	mutex_unlock(&rdata->rp_mutex);

	frport = fcoe_ctlr_rport(rdata);
	LIBFCOE_FIP_DBG(fip, "vn_add rport %6.6x %s state %d\n",
			port_id, frport->fcoe_len ? "old" : "new",
			rdata->rp_state);
	frport->fcoe_len = new->fcoe_len;
	frport->flags = new->flags;
	frport->login_count = new->login_count;
	memcpy(frport->enode_mac, new->enode_mac, ETH_ALEN);
	memcpy(frport->vn_mac, new->vn_mac, ETH_ALEN);
	frport->time = 0;
}