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
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; scalar_t__ vp_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ gpnid; } ;
struct qla_work_evt {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  port_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_GPNID ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  UNLOADING ; 
 int /*<<< orphan*/  VPORT_DELETE ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qla24xx_post_gpnid_work(struct scsi_qla_host *vha, port_id_t *id)
{
	struct qla_work_evt *e;

	if (test_bit(UNLOADING, &vha->dpc_flags) ||
	    (vha->vp_idx && test_bit(VPORT_DELETE, &vha->dpc_flags)))
		return 0;

	e = qla2x00_alloc_work(vha, QLA_EVT_GPNID);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.gpnid.id = *id;
	return qla2x00_post_work(vha, e);
}