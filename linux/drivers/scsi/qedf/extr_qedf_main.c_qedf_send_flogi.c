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
struct qedf_ctx {int /*<<< orphan*/  flogi_compl; int /*<<< orphan*/  dbg_ctx; struct fc_lport* lport; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* elsct_send ) (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {int /*<<< orphan*/  r_a_tov; TYPE_1__ tt; } ;
struct fc_frame {int dummy; } ;
struct fc_els_flogi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ELS_FLOGI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FC_FID_FLOGI ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_flogi_resp ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int /*<<< orphan*/ ) ; 

int qedf_send_flogi(struct qedf_ctx *qedf)
{
	struct fc_lport *lport;
	struct fc_frame *fp;

	lport = qedf->lport;

	if (!lport->tt.elsct_send) {
		QEDF_ERR(&qedf->dbg_ctx, "tt.elsct_send not set.\n");
		return -EINVAL;
	}

	fp = fc_frame_alloc(lport, sizeof(struct fc_els_flogi));
	if (!fp) {
		QEDF_ERR(&(qedf->dbg_ctx), "fc_frame_alloc failed.\n");
		return -ENOMEM;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Sending FLOGI to reestablish session with switch.\n");
	lport->tt.elsct_send(lport, FC_FID_FLOGI, fp,
	    ELS_FLOGI, qedf_flogi_resp, lport, lport->r_a_tov);

	init_completion(&qedf->flogi_compl);

	return 0;
}