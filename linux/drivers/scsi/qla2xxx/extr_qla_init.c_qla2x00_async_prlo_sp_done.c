#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ logio; } ;
struct srb_iocb {TYPE_2__ u; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* free ) (TYPE_4__*) ;TYPE_6__* fcport; struct scsi_qla_host* vha; TYPE_3__ u; } ;
typedef  TYPE_4__ srb_t ;
struct TYPE_12__ {int /*<<< orphan*/  vha; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_ACTIVE ; 
 int /*<<< orphan*/  UNLOADING ; 
 int /*<<< orphan*/  qla2x00_post_async_prlo_done_work (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla2x00_async_prlo_sp_done(srb_t *sp, int res)
{
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	struct scsi_qla_host *vha = sp->vha;

	sp->fcport->flags &= ~FCF_ASYNC_ACTIVE;
	if (!test_bit(UNLOADING, &vha->dpc_flags))
		qla2x00_post_async_prlo_done_work(sp->fcport->vha, sp->fcport,
		    lio->u.logio.data);
	sp->free(sp);
}