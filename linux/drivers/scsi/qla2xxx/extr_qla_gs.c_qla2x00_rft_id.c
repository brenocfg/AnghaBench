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
struct qla_hw_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_id; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int qla2x00_sns_rft_id (TYPE_1__*) ; 
 int qla_async_rftid (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
qla2x00_rft_id(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return qla2x00_sns_rft_id(vha);

	return qla_async_rftid(vha, &vha->d_id);
}