#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int qla8044_device_state_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  qla8044_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_idc_unlock (struct qla_hw_data*) ; 
 int qla82xx_device_state_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  qla83xx_reset_ownership (TYPE_1__*) ; 

int qla82xx_load_risc(scsi_qla_host_t *vha, uint32_t *srisc_addr)
{
	int rval = -1;
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA82XX(ha))
		rval = qla82xx_device_state_handler(vha);
	else if (IS_QLA8044(ha)) {
		qla8044_idc_lock(ha);
		/* Decide the reset ownership */
		qla83xx_reset_ownership(vha);
		qla8044_idc_unlock(ha);
		rval = qla8044_device_state_handler(vha);
	}
	return rval;
}