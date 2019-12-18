#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qla_nvme_rport {TYPE_1__* fcport; } ;
struct nvme_fc_remote_port {struct qla_nvme_rport* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  nvme_del_done; int /*<<< orphan*/  port_name; int /*<<< orphan*/  vha; int /*<<< orphan*/  nvme_flag; int /*<<< orphan*/ * nvme_remote_port; } ;
typedef  TYPE_1__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_FLAG_DELETING ; 
 int /*<<< orphan*/  NVME_FLAG_REGISTERED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_info ; 

__attribute__((used)) static void qla_nvme_remoteport_delete(struct nvme_fc_remote_port *rport)
{
	fc_port_t *fcport;
	struct qla_nvme_rport *qla_rport = rport->private;

	fcport = qla_rport->fcport;
	fcport->nvme_remote_port = NULL;
	fcport->nvme_flag &= ~NVME_FLAG_REGISTERED;
	fcport->nvme_flag &= ~NVME_FLAG_DELETING;
	ql_log(ql_log_info, fcport->vha, 0x2110,
	    "remoteport_delete of %p %8phN completed.\n",
	    fcport, fcport->port_name);
	complete(&fcport->nvme_del_done);
}