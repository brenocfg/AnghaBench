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
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct qla_work_evt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_RELOGIN ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qla24xx_post_relogin_work(struct scsi_qla_host *vha)
{
	struct qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_RELOGIN);

	if (!e) {
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		return QLA_FUNCTION_FAILED;
	}

	return qla2x00_post_work(vha, e);
}