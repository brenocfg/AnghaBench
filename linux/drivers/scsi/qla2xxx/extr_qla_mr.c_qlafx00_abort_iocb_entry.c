#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  comp_status; } ;
struct TYPE_9__ {TYPE_2__ abt; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct req_que {int dummy; } ;
struct abort_iocb_entry_fx00 {int /*<<< orphan*/  tgt_id_sts; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* done ) (TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 TYPE_4__* qla2x00_get_sp_from_handle (int /*<<< orphan*/ *,char const*,struct req_que*,struct abort_iocb_entry_fx00*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlafx00_abort_iocb_entry(scsi_qla_host_t *vha, struct req_que *req,
			 struct abort_iocb_entry_fx00 *pkt)
{
	const char func[] = "ABT_IOCB";
	srb_t *sp;
	struct srb_iocb *abt;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (!sp)
		return;

	abt = &sp->u.iocb_cmd;
	abt->u.abt.comp_status = pkt->tgt_id_sts;
	sp->done(sp, 0);
}