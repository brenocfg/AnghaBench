#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {int nic_core_reset_owner; } ;
struct qla_hw_data {int /*<<< orphan*/  portnum; TYPE_1__ flags; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 scalar_t__ MAX_STATES ; 
 int /*<<< orphan*/  QLA8044_CRB_DEV_STATE_INDEX ; 
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA8XXX_DEV_NEED_RESET ; 
 scalar_t__ QLA8XXX_DEV_READY ; 
 char* qdev_state (scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 scalar_t__ qla8044_rd_direct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla8044_wr_direct (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qla82xx_set_reset_owner(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t dev_state = 0;

	if (IS_QLA82XX(ha))
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	else if (IS_QLA8044(ha))
		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

	if (dev_state == QLA8XXX_DEV_READY) {
		ql_log(ql_log_info, vha, 0xb02f,
		    "HW State: NEED RESET\n");
		if (IS_QLA82XX(ha)) {
			qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
			    QLA8XXX_DEV_NEED_RESET);
			ha->flags.nic_core_reset_owner = 1;
			ql_dbg(ql_dbg_p3p, vha, 0xb030,
			    "reset_owner is 0x%x\n", ha->portnum);
		} else if (IS_QLA8044(ha))
			qla8044_wr_direct(vha, QLA8044_CRB_DEV_STATE_INDEX,
			    QLA8XXX_DEV_NEED_RESET);
	} else
		ql_log(ql_log_info, vha, 0xb031,
		    "Device state is 0x%x = %s.\n",
		    dev_state,
		    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");
}