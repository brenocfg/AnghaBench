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
struct qedf_ctx {scalar_t__ fipvlan_retries; scalar_t__ vlan_id; int /*<<< orphan*/  fipvlan_compl; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  link_state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ QEDF_LINK_DOWN ; 
 scalar_t__ QEDF_LINK_UP ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_ctlr_link_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_fcoe_send_vlan_req (struct qedf_ctx*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool qedf_initiate_fipvlan_req(struct qedf_ctx *qedf)
{

	while (qedf->fipvlan_retries--) {
		/* This is to catch if link goes down during fipvlan retries */
		if (atomic_read(&qedf->link_state) == QEDF_LINK_DOWN) {
			QEDF_ERR(&qedf->dbg_ctx, "Link not up.\n");
			return false;
		}

		if (test_bit(QEDF_UNLOADING, &qedf->flags)) {
			QEDF_ERR(&qedf->dbg_ctx, "Driver unloading.\n");
			return false;
		}

		if (qedf->vlan_id > 0) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "vlan = 0x%x already set, calling ctlr_link_up.\n",
				  qedf->vlan_id);
			if (atomic_read(&qedf->link_state) == QEDF_LINK_UP)
				fcoe_ctlr_link_up(&qedf->ctlr);
			return true;
		}

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			   "Retry %d.\n", qedf->fipvlan_retries);
		init_completion(&qedf->fipvlan_compl);
		qedf_fcoe_send_vlan_req(qedf);
		wait_for_completion_timeout(&qedf->fipvlan_compl, 1 * HZ);
	}

	return false;
}