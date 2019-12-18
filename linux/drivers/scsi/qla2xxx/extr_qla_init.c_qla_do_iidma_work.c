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
struct scsi_qla_host {int dummy; } ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla24xx_update_fcport_fcp_prio (struct scsi_qla_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_iidma_fcport (struct scsi_qla_host*,int /*<<< orphan*/ *) ; 

void qla_do_iidma_work(struct scsi_qla_host *vha, fc_port_t *fcport)
{
	qla2x00_iidma_fcport(vha, fcport);
	qla24xx_update_fcport_fcp_prio(vha, fcport);
}