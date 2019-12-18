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
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 int DONTRESET_BIT0 ; 
 int /*<<< orphan*/  QLA8044_IDC_DRV_CTRL ; 
 int qla8044_rd_reg (struct qla_hw_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla8044_idc_dontreset(struct qla_hw_data *ha)
{
	uint32_t idc_ctrl;

	idc_ctrl = qla8044_rd_reg(ha, QLA8044_IDC_DRV_CTRL);
	return idc_ctrl & DONTRESET_BIT0;
}