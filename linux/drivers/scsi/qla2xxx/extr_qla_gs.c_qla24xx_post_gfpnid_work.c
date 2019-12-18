#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  loop_state; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fcport; } ;
struct TYPE_4__ {TYPE_1__ fcport; } ;
struct qla_work_evt {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int LOOP_READY ; 
 int LOOP_UP ; 
 int /*<<< orphan*/  QLA_EVT_GFPNID ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  UNLOADING ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qla24xx_post_gfpnid_work(struct scsi_qla_host *vha, fc_port_t *fcport)
{
	struct qla_work_evt *e;
	int ls;

	ls = atomic_read(&vha->loop_state);
	if (((ls != LOOP_READY) && (ls != LOOP_UP)) ||
		test_bit(UNLOADING, &vha->dpc_flags))
		return 0;

	e = qla2x00_alloc_work(vha, QLA_EVT_GFPNID);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	return qla2x00_post_work(vha, e);
}