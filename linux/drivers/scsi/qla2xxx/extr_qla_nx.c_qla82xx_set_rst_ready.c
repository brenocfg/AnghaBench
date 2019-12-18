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
struct qla_hw_data {int portnum; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DRV_STATE ; 
 int QLA82XX_DRVST_NOT_RDY ; 
 int QLA82XX_DRVST_RST_RDY ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
qla82xx_set_rst_ready(struct qla_hw_data *ha)
{
	uint32_t drv_state;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);

	/* If reset value is all FF's, initialize DRV_STATE */
	if (drv_state == 0xffffffff) {
		qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, QLA82XX_DRVST_NOT_RDY);
		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	}
	drv_state |= (QLA82XX_DRVST_RST_RDY << (ha->portnum * 4));
	ql_dbg(ql_dbg_init, vha, 0x00bb,
	    "drv_state = 0x%08x.\n", drv_state);
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, drv_state);
}