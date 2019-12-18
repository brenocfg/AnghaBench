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
struct qla_hw_data {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_FLASH_LOCK_ID ; 
 int /*<<< orphan*/  QLA8044_FLASH_UNLOCK ; 
 int /*<<< orphan*/  qla8044_rd_reg (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla8044_wr_reg (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qla8044_flash_unlock(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	/* Reading FLASH_UNLOCK register unlocks the Flash */
	qla8044_wr_reg(ha, QLA8044_FLASH_LOCK_ID, 0xFF);
	qla8044_rd_reg(ha, QLA8044_FLASH_UNLOCK);
}