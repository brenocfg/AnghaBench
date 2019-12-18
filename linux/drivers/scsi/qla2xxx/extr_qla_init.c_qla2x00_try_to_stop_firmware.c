#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ fw_init_done; int /*<<< orphan*/  fw_started; scalar_t__ pci_channel_io_perm_failure; } ;
struct qla_hw_data {TYPE_2__ flags; TYPE_1__* isp_ops; int /*<<< orphan*/  fw_major_version; } ;
struct TYPE_12__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_10__ {int (* chip_diag ) (TYPE_3__*) ;int /*<<< orphan*/  (* reset_chip ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int QLA_FUNCTION_TIMEOUT ; 
 int /*<<< orphan*/  QLA_FW_STOPPED (struct qla_hw_data*) ; 
 int QLA_INVALID_COMMAND ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int qla2x00_setup_chip (TYPE_3__*) ; 
 int qla2x00_stop_firmware (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int stub2 (TYPE_3__*) ; 

void
qla2x00_try_to_stop_firmware(scsi_qla_host_t *vha)
{
	int ret, retries;
	struct qla_hw_data *ha = vha->hw;

	if (ha->flags.pci_channel_io_perm_failure)
		return;
	if (!IS_FWI2_CAPABLE(ha))
		return;
	if (!ha->fw_major_version)
		return;
	if (!ha->flags.fw_started)
		return;

	ret = qla2x00_stop_firmware(vha);
	for (retries = 5; ret != QLA_SUCCESS && ret != QLA_FUNCTION_TIMEOUT &&
	    ret != QLA_INVALID_COMMAND && retries ; retries--) {
		ha->isp_ops->reset_chip(vha);
		if (ha->isp_ops->chip_diag(vha) != QLA_SUCCESS)
			continue;
		if (qla2x00_setup_chip(vha) != QLA_SUCCESS)
			continue;
		ql_log(ql_log_info, vha, 0x8015,
		    "Attempting retry of stop-firmware command.\n");
		ret = qla2x00_stop_firmware(vha);
	}

	QLA_FW_STOPPED(ha);
	ha->flags.fw_init_done = 0;
}