#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct qla_hw_data {TYPE_2__* isp_ops; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  target_reset; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  WAIT_TARGET ; 
 int __qla2xxx_eh_generic_reset (char*,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 scalar_t__ qla2x00_isp_reg_stat (struct qla_hw_data*) ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2xxx_eh_target_reset(struct scsi_cmnd *cmd)
{
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	struct qla_hw_data *ha = vha->hw;

	if (qla2x00_isp_reg_stat(ha)) {
		ql_log(ql_log_info, vha, 0x803f,
		    "PCI/Register disconnect, exiting.\n");
		return FAILED;
	}

	return __qla2xxx_eh_generic_reset("TARGET", WAIT_TARGET, cmd,
	    ha->isp_ops->target_reset);
}