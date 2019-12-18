#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* idc_unlock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_lock ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __qla4_83xx_disable_pause (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_dump_pause_control_regs (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_eport_init (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 

void qla4_83xx_disable_pause(struct scsi_qla_host *ha)
{
	ha->isp_ops->idc_lock(ha);
	/* Before disabling pause frames, ensure that eport is not in reset */
	qla4_83xx_eport_init(ha);
	qla4_83xx_dump_pause_control_regs(ha);
	__qla4_83xx_disable_pause(ha);
	ha->isp_ops->idc_unlock(ha);
}