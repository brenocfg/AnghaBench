#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {unsigned long fcoe_reset_timeout; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  QLA83XX_IDC_DEV_STATE ; 
 int /*<<< orphan*/  QLA83XX_IDC_DRIVER_ACK ; 
 int /*<<< orphan*/  QLA83XX_IDC_DRV_PRESENCE ; 
 int QLA8XXX_DEV_COLD ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla83xx_idc_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_idc_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_rd_reg (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qla83xx_wr_reg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void
qla83xx_need_reset_handler(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t drv_ack, drv_presence;
	unsigned long ack_timeout;

	/* Wait for IDC ACK from all functions (DRV-ACK == DRV-PRESENCE) */
	ack_timeout = jiffies + (ha->fcoe_reset_timeout * HZ);
	while (1) {
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRIVER_ACK, &drv_ack);
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
		if ((drv_ack & drv_presence) == drv_presence)
			break;

		if (time_after_eq(jiffies, ack_timeout)) {
			ql_log(ql_log_warn, vha, 0xb067,
			    "RESET ACK TIMEOUT! drv_presence=0x%x "
			    "drv_ack=0x%x\n", drv_presence, drv_ack);
			/*
			 * The function(s) which did not ack in time are forced
			 * to withdraw any further participation in the IDC
			 * reset.
			 */
			if (drv_ack != drv_presence)
				qla83xx_wr_reg(vha, QLA83XX_IDC_DRV_PRESENCE,
				    drv_ack);
			break;
		}

		qla83xx_idc_unlock(vha, 0);
		msleep(1000);
		qla83xx_idc_lock(vha, 0);
	}

	qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_COLD);
	ql_log(ql_log_info, vha, 0xb068, "HW State: COLD/RE-INIT.\n");
}