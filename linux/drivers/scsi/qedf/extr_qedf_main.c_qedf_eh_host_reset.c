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
struct scsi_cmnd {TYPE_1__* device; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  link_state; } ;
struct fc_lport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ QEDF_LINK_DOWN ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 int SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  qedf_ctx_soft_reset (struct fc_lport*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_eh_host_reset(struct scsi_cmnd *sc_cmd)
{
	struct fc_lport *lport;
	struct qedf_ctx *qedf;

	lport = shost_priv(sc_cmd->device->host);
	qedf = lport_priv(lport);

	if (atomic_read(&qedf->link_state) == QEDF_LINK_DOWN ||
	    test_bit(QEDF_UNLOADING, &qedf->flags))
		return FAILED;

	QEDF_ERR(&(qedf->dbg_ctx), "HOST RESET Issued...");

	qedf_ctx_soft_reset(lport);

	return SUCCESS;
}