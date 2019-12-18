#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nic_core_reset_hdlr_active; } ;
struct qla_hw_data {int /*<<< orphan*/  nic_core_unrecoverable; int /*<<< orphan*/  dpc_hp_wq; int /*<<< orphan*/  idc_state_handler; int /*<<< orphan*/  nic_core_reset; TYPE_1__ flags; int /*<<< orphan*/  idc_aen; int /*<<< orphan*/  dpc_lp_wq; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
#define  MBA_IDC_AEN 131 
#define  QLA83XX_IDC_STATE_HANDLER 130 
#define  QLA83XX_NIC_CORE_RESET 129 
#define  QLA83XX_NIC_CORE_UNRECOVERABLE 128 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla83xx_schedule_work(scsi_qla_host_t *base_vha, int work_code)
{
	struct qla_hw_data *ha = base_vha->hw;

	switch (work_code) {
	case MBA_IDC_AEN: /* 0x8200 */
		if (ha->dpc_lp_wq)
			queue_work(ha->dpc_lp_wq, &ha->idc_aen);
		break;

	case QLA83XX_NIC_CORE_RESET: /* 0x1 */
		if (!ha->flags.nic_core_reset_hdlr_active) {
			if (ha->dpc_hp_wq)
				queue_work(ha->dpc_hp_wq, &ha->nic_core_reset);
		} else
			ql_dbg(ql_dbg_p3p, base_vha, 0xb05e,
			    "NIC Core reset is already active. Skip "
			    "scheduling it again.\n");
		break;
	case QLA83XX_IDC_STATE_HANDLER: /* 0x2 */
		if (ha->dpc_hp_wq)
			queue_work(ha->dpc_hp_wq, &ha->idc_state_handler);
		break;
	case QLA83XX_NIC_CORE_UNRECOVERABLE: /* 0x3 */
		if (ha->dpc_hp_wq)
			queue_work(ha->dpc_hp_wq, &ha->nic_core_unrecoverable);
		break;
	default:
		ql_log(ql_log_warn, base_vha, 0xb05f,
		    "Unknown work-code=0x%x.\n", work_code);
	}

	return;
}