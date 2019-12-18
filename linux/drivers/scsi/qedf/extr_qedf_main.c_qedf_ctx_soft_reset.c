#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qedf_ctx {int /*<<< orphan*/  link_update; int /*<<< orphan*/  link_update_wq; int /*<<< orphan*/  dbg_ctx; scalar_t__ vlan_id; int /*<<< orphan*/  link_state; int /*<<< orphan*/  cdev; int /*<<< orphan*/  num_offloads; } ;
struct qed_link_output {int /*<<< orphan*/  link_up; } ;
struct fc_lport {scalar_t__ vport; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_output*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LINK_DOWN ; 
 int /*<<< orphan*/  QEDF_LINK_UP ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* qed_ops ; 
 int qedf_wait_for_upload (struct qedf_ctx*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_link_output*) ; 

void qedf_ctx_soft_reset(struct fc_lport *lport)
{
	struct qedf_ctx *qedf;
	struct qed_link_output if_link;

	if (lport->vport) {
		QEDF_ERR(NULL, "Cannot issue host reset on NPIV port.\n");
		return;
	}

	qedf = lport_priv(lport);

	/* For host reset, essentially do a soft link up/down */
	atomic_set(&qedf->link_state, QEDF_LINK_DOWN);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Queuing link down work.\n");
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);

	if (qedf_wait_for_upload(qedf) == false) {
		QEDF_ERR(&qedf->dbg_ctx, "Could not upload all sessions.\n");
		WARN_ON(atomic_read(&qedf->num_offloads));
	}

	/* Before setting link up query physical link state */
	qed_ops->common->get_link(qedf->cdev, &if_link);
	/* Bail if the physical link is not up */
	if (!if_link.link_up) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "Physical link is not up.\n");
		return;
	}
	/* Flush and wait to make sure link down is processed */
	flush_delayed_work(&qedf->link_update);
	msleep(500);

	atomic_set(&qedf->link_state, QEDF_LINK_UP);
	qedf->vlan_id  = 0;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Queue link up work.\n");
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);
}