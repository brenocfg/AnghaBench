#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct req_que {scalar_t__ ring; } ;
struct qla_hw_data {void* fcoe_reset_timeout; void* fcoe_dev_init_timeout; TYPE_1__* isp_ops; struct req_que** req_q_map; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* read_optrom ) (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_P3P_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA82XX_IDC_PARAM_ADDR ; 
 void* QLA82XX_ROM_DEV_INIT_TIMEOUT ; 
 void* QLA82XX_ROM_DRV_RESET_ACK_TIMEOUT ; 
 scalar_t__ cpu_to_le32 (int) ; 
 void* le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,void*,void*) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qla2xxx_get_idc_param(scsi_qla_host_t *vha)
{
#define QLA82XX_IDC_PARAM_ADDR       0x003e885c
	uint32_t *wptr;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];

	if (!(IS_P3P_TYPE(ha)))
		return;

	wptr = (uint32_t *)req->ring;
	ha->isp_ops->read_optrom(vha, req->ring, QLA82XX_IDC_PARAM_ADDR, 8);

	if (*wptr == cpu_to_le32(0xffffffff)) {
		ha->fcoe_dev_init_timeout = QLA82XX_ROM_DEV_INIT_TIMEOUT;
		ha->fcoe_reset_timeout = QLA82XX_ROM_DRV_RESET_ACK_TIMEOUT;
	} else {
		ha->fcoe_dev_init_timeout = le32_to_cpu(*wptr);
		wptr++;
		ha->fcoe_reset_timeout = le32_to_cpu(*wptr);
	}
	ql_dbg(ql_dbg_init, vha, 0x004e,
	    "fcoe_dev_init_timeout=%d "
	    "fcoe_reset_timeout=%d.\n", ha->fcoe_dev_init_timeout,
	    ha->fcoe_reset_timeout);
	return;
}