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
typedef  struct qedf_rport* u32 ;
struct qedf_rport {int /*<<< orphan*/  flags; struct fc_rport_priv* rdata; TYPE_2__* qedf; int /*<<< orphan*/  rport_lock; } ;
struct TYPE_4__ {struct qedf_rport* port_id; } ;
struct fc_rport_priv {scalar_t__ rp_state; int /*<<< orphan*/  kref; TYPE_1__ ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_3__ disc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dbg_ctx; struct fc_lport* lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_RESET ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  QEDF_RPORT_UPLOADING_CONNECTION ; 
 scalar_t__ RPORT_ST_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fc_rport_priv* fc_rport_create (struct fc_lport*,struct qedf_rport*) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_login (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_logoff (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_restart_rport(struct qedf_rport *fcport)
{
	struct fc_lport *lport;
	struct fc_rport_priv *rdata;
	u32 port_id;
	unsigned long flags;

	if (!fcport) {
		QEDF_ERR(NULL, "fcport is NULL.\n");
		return;
	}

	spin_lock_irqsave(&fcport->rport_lock, flags);
	if (test_bit(QEDF_RPORT_IN_RESET, &fcport->flags) ||
	    !test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "fcport %p already in reset or not offloaded.\n",
		    fcport);
		spin_unlock_irqrestore(&fcport->rport_lock, flags);
		return;
	}

	/* Set that we are now in reset */
	set_bit(QEDF_RPORT_IN_RESET, &fcport->flags);
	spin_unlock_irqrestore(&fcport->rport_lock, flags);

	rdata = fcport->rdata;
	if (rdata && !kref_get_unless_zero(&rdata->kref)) {
		fcport->rdata = NULL;
		rdata = NULL;
	}

	if (rdata && rdata->rp_state == RPORT_ST_READY) {
		lport = fcport->qedf->lport;
		port_id = rdata->ids.port_id;
		QEDF_ERR(&(fcport->qedf->dbg_ctx),
		    "LOGO port_id=%x.\n", port_id);
		fc_rport_logoff(rdata);
		kref_put(&rdata->kref, fc_rport_destroy);
		mutex_lock(&lport->disc.disc_mutex);
		/* Recreate the rport and log back in */
		rdata = fc_rport_create(lport, port_id);
		if (rdata) {
			mutex_unlock(&lport->disc.disc_mutex);
			fc_rport_login(rdata);
			fcport->rdata = rdata;
		} else {
			mutex_unlock(&lport->disc.disc_mutex);
			fcport->rdata = NULL;
		}
	}
	clear_bit(QEDF_RPORT_IN_RESET, &fcport->flags);
}