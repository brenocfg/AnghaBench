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
typedef  int uint32_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  nic_core_reset_owner; } ;
struct qla_hw_data {unsigned long fcoe_dev_init_timeout; unsigned long fcoe_reset_timeout; TYPE_1__ flags; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int MAX_STATES ; 
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int /*<<< orphan*/  QLA8044_CRB_DEV_STATE_INDEX ; 
#define  QLA8XXX_DEV_COLD 134 
#define  QLA8XXX_DEV_FAILED 133 
#define  QLA8XXX_DEV_INITIALIZING 132 
#define  QLA8XXX_DEV_NEED_QUIESCENT 131 
#define  QLA8XXX_DEV_NEED_RESET 130 
#define  QLA8XXX_DEV_QUIESCENT 129 
#define  QLA8XXX_DEV_READY 128 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 char* qdev_state (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla8044_check_drv_active (struct scsi_qla_host*) ; 
 int qla8044_device_bootstrap (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla8044_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_idc_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_need_qsnt_handler (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla8044_need_reset_handler (struct scsi_qla_host*) ; 
 int qla8044_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla8044_update_idc_reg (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla8044_wr_direct (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla8xxx_dev_failed_handler (struct scsi_qla_host*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int
qla8044_device_state_handler(struct scsi_qla_host *vha)
{
	uint32_t dev_state;
	int rval = QLA_SUCCESS;
	unsigned long dev_init_timeout;
	struct qla_hw_data *ha = vha->hw;

	rval = qla8044_update_idc_reg(vha);
	if (rval == QLA_FUNCTION_FAILED)
		goto exit_error;

	dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);
	ql_dbg(ql_dbg_p3p, vha, 0xb0ce,
	    "Device state is 0x%x = %s\n",
	    dev_state, dev_state < MAX_STATES ?
	    qdev_state(dev_state) : "Unknown");

	/* wait for 30 seconds for device to go ready */
	dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout * HZ);

	qla8044_idc_lock(ha);

	while (1) {
		if (time_after_eq(jiffies, dev_init_timeout)) {
			if (qla8044_check_drv_active(vha) == QLA_SUCCESS) {
				ql_log(ql_log_warn, vha, 0xb0cf,
				    "%s: Device Init Failed 0x%x = %s\n",
				    QLA2XXX_DRIVER_NAME, dev_state,
				    dev_state < MAX_STATES ?
				    qdev_state(dev_state) : "Unknown");
				qla8044_wr_direct(vha,
				    QLA8044_CRB_DEV_STATE_INDEX,
				    QLA8XXX_DEV_FAILED);
			}
		}

		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);
		ql_log(ql_log_info, vha, 0xb0d0,
		    "Device state is 0x%x = %s\n",
		    dev_state, dev_state < MAX_STATES ?
		    qdev_state(dev_state) : "Unknown");

		/* NOTE: Make sure idc unlocked upon exit of switch statement */
		switch (dev_state) {
		case QLA8XXX_DEV_READY:
			ha->flags.nic_core_reset_owner = 0;
			goto exit;
		case QLA8XXX_DEV_COLD:
			rval = qla8044_device_bootstrap(vha);
			break;
		case QLA8XXX_DEV_INITIALIZING:
			qla8044_idc_unlock(ha);
			msleep(1000);
			qla8044_idc_lock(ha);
			break;
		case QLA8XXX_DEV_NEED_RESET:
			/* For ISP8044, if NEED_RESET is set by any driver,
			 * it should be honored, irrespective of IDC_CTRL
			 * DONTRESET_BIT0 */
			qla8044_need_reset_handler(vha);
			break;
		case QLA8XXX_DEV_NEED_QUIESCENT:
			/* idc locked/unlocked in handler */
			qla8044_need_qsnt_handler(vha);

			/* Reset the init timeout after qsnt handler */
			dev_init_timeout = jiffies +
			    (ha->fcoe_reset_timeout * HZ);
			break;
		case QLA8XXX_DEV_QUIESCENT:
			ql_log(ql_log_info, vha, 0xb0d1,
			    "HW State: QUIESCENT\n");

			qla8044_idc_unlock(ha);
			msleep(1000);
			qla8044_idc_lock(ha);

			/* Reset the init timeout after qsnt handler */
			dev_init_timeout = jiffies +
			    (ha->fcoe_reset_timeout * HZ);
			break;
		case QLA8XXX_DEV_FAILED:
			ha->flags.nic_core_reset_owner = 0;
			qla8044_idc_unlock(ha);
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			qla8044_idc_lock(ha);
			goto exit;
		default:
			qla8044_idc_unlock(ha);
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			qla8044_idc_lock(ha);
			goto exit;
		}
	}
exit:
	qla8044_idc_unlock(ha);

exit_error:
	return rval;
}