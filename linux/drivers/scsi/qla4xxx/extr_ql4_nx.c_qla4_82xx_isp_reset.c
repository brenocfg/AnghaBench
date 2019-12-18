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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_8XXX_RST_OWNER ; 
 int /*<<< orphan*/  AF_FW_RECOVERY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA8XXX_DEV_NEED_RESET ; 
 scalar_t__ QLA8XXX_DEV_READY ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4_82xx_idc_lock (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_idc_unlock (struct scsi_qla_host*) ; 
 scalar_t__ qla4_82xx_rd_32 (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_82xx_wr_32 (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_8xxx_clear_rst_ready (struct scsi_qla_host*) ; 
 int qla4_8xxx_device_state_handler (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla4_82xx_isp_reset(struct scsi_qla_host *ha)
{
	int rval;
	uint32_t dev_state;

	qla4_82xx_idc_lock(ha);
	dev_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);

	if (dev_state == QLA8XXX_DEV_READY) {
		ql4_printk(KERN_INFO, ha, "HW State: NEED RESET\n");
		qla4_82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
		    QLA8XXX_DEV_NEED_RESET);
		set_bit(AF_8XXX_RST_OWNER, &ha->flags);
	} else
		ql4_printk(KERN_INFO, ha, "HW State: DEVICE INITIALIZING\n");

	qla4_82xx_idc_unlock(ha);

	rval = qla4_8xxx_device_state_handler(ha);

	qla4_82xx_idc_lock(ha);
	qla4_8xxx_clear_rst_ready(ha);
	qla4_82xx_idc_unlock(ha);

	if (rval == QLA_SUCCESS) {
		ql4_printk(KERN_INFO, ha, "Clearing AF_RECOVERY in qla4_82xx_isp_reset\n");
		clear_bit(AF_FW_RECOVERY, &ha->flags);
	}

	return rval;
}