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
struct qla_hw_data {int portnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DRV_STATE ; 
 int QLA82XX_DRVST_RST_RDY ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
qla82xx_clear_rst_ready(struct qla_hw_data *ha)
{
	uint32_t drv_state;

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_state &= ~(QLA82XX_DRVST_RST_RDY << (ha->portnum * 4));
	qla82xx_wr_32(ha, QLA82XX_CRB_DRV_STATE, drv_state);
}