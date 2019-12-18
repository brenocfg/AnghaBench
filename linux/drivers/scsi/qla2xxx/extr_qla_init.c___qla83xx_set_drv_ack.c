#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {int portnum; } ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_IDC_DRIVER_ACK ; 
 int QLA_SUCCESS ; 
 int qla83xx_rd_reg (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int qla83xx_wr_reg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
__qla83xx_set_drv_ack(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;
	uint32_t drv_ack;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRIVER_ACK, &drv_ack);
	if (rval == QLA_SUCCESS) {
		drv_ack |= (1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRIVER_ACK, drv_ack);
	}

	return rval;
}