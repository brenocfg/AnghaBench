#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct logio_entry_24xx {int /*<<< orphan*/  vp_index; int /*<<< orphan*/ * port_id; void* nport_handle; void* control_flags; int /*<<< orphan*/  entry_type; } ;
struct TYPE_11__ {TYPE_4__* fcport; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_7__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_10__ {int loop_id; TYPE_3__* vha; TYPE_2__ d_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  vp_idx; } ;

/* Variables and functions */
 int LCF_COMMAND_PRLO ; 
 int LCF_IMPL_PRLO ; 
 int /*<<< orphan*/  LOGINOUT_PORT_IOCB_TYPE ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
qla24xx_prlo_iocb(srb_t *sp, struct logio_entry_24xx *logio)
{
	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags =
	    cpu_to_le16(LCF_COMMAND_PRLO|LCF_IMPL_PRLO);

	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->port_id[0] = sp->fcport->d_id.b.al_pa;
	logio->port_id[1] = sp->fcport->d_id.b.area;
	logio->port_id[2] = sp->fcport->d_id.b.domain;
	logio->vp_index = sp->fcport->vha->vp_idx;
}