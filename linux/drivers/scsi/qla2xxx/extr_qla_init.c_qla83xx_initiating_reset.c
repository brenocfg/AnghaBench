#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {scalar_t__ nic_core_reset_owner; } ;
struct qla_hw_data {TYPE_1__ flags; } ;
struct TYPE_13__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_AUDIT_TIMESTAMP ; 
 int /*<<< orphan*/  QLA83XX_IDC_DEV_STATE ; 
 int QLA83XX_IDC_RESET_DISABLED ; 
 int /*<<< orphan*/  QLA8XXX_DEV_NEED_RESET ; 
 int QLA8XXX_DEV_READY ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  __qla83xx_get_idc_control (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  __qla83xx_set_drv_ack (TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 char* qla83xx_dev_state_to_string (int) ; 
 int /*<<< orphan*/  qla83xx_idc_audit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_idc_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_idc_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_rd_reg (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qla83xx_wr_reg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla83xx_initiating_reset(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t  idc_control, dev_state;

	__qla83xx_get_idc_control(vha, &idc_control);
	if ((idc_control & QLA83XX_IDC_RESET_DISABLED)) {
		ql_log(ql_log_info, vha, 0xb080,
		    "NIC Core reset has been disabled. idc-control=0x%x\n",
		    idc_control);
		return QLA_FUNCTION_FAILED;
	}

	/* Set NEED-RESET iff in READY state and we are the reset-owner */
	qla83xx_rd_reg(vha, QLA83XX_IDC_DEV_STATE, &dev_state);
	if (ha->flags.nic_core_reset_owner && dev_state == QLA8XXX_DEV_READY) {
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE,
		    QLA8XXX_DEV_NEED_RESET);
		ql_log(ql_log_info, vha, 0xb056, "HW State: NEED RESET.\n");
		qla83xx_idc_audit(vha, IDC_AUDIT_TIMESTAMP);
	} else {
		const char *state = qla83xx_dev_state_to_string(dev_state);

		ql_log(ql_log_info, vha, 0xb057, "HW State: %s.\n", state);

		/* SV: XXX: Is timeout required here? */
		/* Wait for IDC state change READY -> NEED_RESET */
		while (dev_state == QLA8XXX_DEV_READY) {
			qla83xx_idc_unlock(vha, 0);
			msleep(200);
			qla83xx_idc_lock(vha, 0);
			qla83xx_rd_reg(vha, QLA83XX_IDC_DEV_STATE, &dev_state);
		}
	}

	/* Send IDC ack by writing to drv-ack register */
	__qla83xx_set_drv_ack(vha);

	return QLA_SUCCESS;
}