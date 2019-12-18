#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  comp; } ;
struct TYPE_12__ {TYPE_4__ els_logo; } ;
struct srb_iocb {TYPE_5__ u; } ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_8__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_13__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  name; TYPE_1__ u; struct scsi_qla_host* vha; TYPE_7__* fcport; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_9__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_10__ {TYPE_2__ b; } ;
struct TYPE_14__ {TYPE_3__ d_id; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_io ; 

__attribute__((used)) static void
qla2x00_els_dcmd_iocb_timeout(void *data)
{
	srb_t *sp = data;
	fc_port_t *fcport = sp->fcport;
	struct scsi_qla_host *vha = sp->vha;
	struct srb_iocb *lio = &sp->u.iocb_cmd;

	ql_dbg(ql_dbg_io, vha, 0x3069,
	    "%s Timeout, hdl=%x, portid=%02x%02x%02x\n",
	    sp->name, sp->handle, fcport->d_id.b.domain, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa);

	complete(&lio->u.els_logo.comp);
}