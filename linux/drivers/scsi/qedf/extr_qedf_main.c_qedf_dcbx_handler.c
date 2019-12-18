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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qedf_ctx {int prio; int /*<<< orphan*/  link_down_tmo_valid; int /*<<< orphan*/  link_update; int /*<<< orphan*/  link_update_wq; int /*<<< orphan*/  link_recovery; int /*<<< orphan*/  link_state; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  dcbx; } ;
struct TYPE_3__ {int fcoe; } ;
struct TYPE_4__ {TYPE_1__ app_prio; int /*<<< orphan*/  valid; int /*<<< orphan*/  enabled; } ;
struct qed_dcbx_get {TYPE_2__ operational; } ;

/* Variables and functions */
 scalar_t__ QEDF_DCBX_DONE ; 
 int QEDF_DEFAULT_PRIO ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ QEDF_LINK_UP ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qedf_dcbx_no_wait ; 
 int qedf_default_prio ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_dcbx_handler(void *dev, struct qed_dcbx_get *get, u32 mib_type)
{
	struct qedf_ctx *qedf = (struct qedf_ctx *)dev;
	u8 tmp_prio;

	QEDF_ERR(&(qedf->dbg_ctx), "DCBx event valid=%d enabled=%d fcoe "
	    "prio=%d.\n", get->operational.valid, get->operational.enabled,
	    get->operational.app_prio.fcoe);

	if (get->operational.enabled && get->operational.valid) {
		/* If DCBX was already negotiated on link up then just exit */
		if (atomic_read(&qedf->dcbx) == QEDF_DCBX_DONE) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "DCBX already set on link up.\n");
			return;
		}

		atomic_set(&qedf->dcbx, QEDF_DCBX_DONE);

		/*
		 * Set the 8021q priority in the following manner:
		 *
		 * 1. If a modparam is set use that
		 * 2. If the value is not between 0..7 use the default
		 * 3. Use the priority we get from the DCBX app tag
		 */
		tmp_prio = get->operational.app_prio.fcoe;
		if (qedf_default_prio > -1)
			qedf->prio = qedf_default_prio;
		else if (tmp_prio > 7) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "FIP/FCoE prio %d out of range, setting to %d.\n",
			    tmp_prio, QEDF_DEFAULT_PRIO);
			qedf->prio = QEDF_DEFAULT_PRIO;
		} else
			qedf->prio = tmp_prio;

		if (atomic_read(&qedf->link_state) == QEDF_LINK_UP &&
		    !qedf_dcbx_no_wait) {
			if (atomic_read(&qedf->link_down_tmo_valid) > 0)
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_recovery, 0);
			else
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_update, 0);
			atomic_set(&qedf->link_down_tmo_valid, 0);
		}
	}

}