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
typedef  int uint32_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int DONTRESET_BIT0 ; 
 int /*<<< orphan*/  QLA83XX_IDC_DRV_CTRL ; 
 int qla4_83xx_rd_reg (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 

int qla4_83xx_idc_dontreset(struct scsi_qla_host *ha)
{
	uint32_t idc_ctrl;

	idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
	return idc_ctrl & DONTRESET_BIT0;
}