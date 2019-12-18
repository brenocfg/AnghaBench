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
struct scsi_qla_host {int /*<<< orphan*/  nvme_del_done; scalar_t__ nvme_local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NVME_FC ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int nvme_fc_unregister_localport (scalar_t__) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void qla_nvme_delete(struct scsi_qla_host *vha)
{
	int nv_ret;

	if (!IS_ENABLED(CONFIG_NVME_FC))
		return;

	if (vha->nvme_local_port) {
		init_completion(&vha->nvme_del_done);
		ql_log(ql_log_info, vha, 0x2116,
			"unregister localport=%p\n",
			vha->nvme_local_port);
		nv_ret = nvme_fc_unregister_localport(vha->nvme_local_port);
		if (nv_ret)
			ql_log(ql_log_info, vha, 0x2115,
			    "Unregister of localport failed\n");
		else
			wait_for_completion(&vha->nvme_del_done);
	}
}