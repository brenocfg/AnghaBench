#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {int portnum; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DRV_STATE ; 
 int QLA82XX_DRVST_QSNT_RDY ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 

void
qla82xx_clear_qsnt_ready(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t qsnt_state;

	qsnt_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	qsnt_state &= ~(QLA82XX_DRVST_QSNT_RDY << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, qsnt_state);
}