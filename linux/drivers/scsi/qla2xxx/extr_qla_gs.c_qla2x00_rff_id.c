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
typedef  int /*<<< orphan*/  u8 ;
struct qla_hw_data {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_id; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC4_TYPE_FCP_SCSI ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla_async_rffid (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_rff_id (TYPE_1__*) ; 

int
qla2x00_rff_id(scsi_qla_host_t *vha, u8 type)
{
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA2100(ha) || IS_QLA2200(ha)) {
		ql_dbg(ql_dbg_disc, vha, 0x2046,
		    "RFF_ID call not supported on ISP2100/ISP2200.\n");
		return (QLA_SUCCESS);
	}

	return qla_async_rffid(vha, &vha->d_id, qlt_rff_id(vha),
	    FC4_TYPE_FCP_SCSI);
}