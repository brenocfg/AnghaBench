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
struct qla_hw_data {int dummy; } ;
struct mbx_entry {void* mb9; void* mb3; void* mb2; void* mb1; void* mb0; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  entry_type; } ;
struct TYPE_11__ {TYPE_4__* vha; TYPE_3__* fcport; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_10__ {int vp_idx; struct qla_hw_data* hw; } ;
struct TYPE_7__ {int domain; int area; int al_pa; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_9__ {int loop_id; TYPE_2__ d_id; } ;

/* Variables and functions */
 scalar_t__ HAS_EXTENDED_IDS (struct qla_hw_data*) ; 
 int MBC_LOGOUT_FABRIC_PORT ; 
 int /*<<< orphan*/  MBX_IOCB_TYPE ; 
 int /*<<< orphan*/  SET_TARGET_ID (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
qla2x00_logout_iocb(srb_t *sp, struct mbx_entry *mbx)
{
	struct qla_hw_data *ha = sp->vha->hw;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_LOGOUT_FABRIC_PORT);
	mbx->mb1 = HAS_EXTENDED_IDS(ha) ?
	    cpu_to_le16(sp->fcport->loop_id) :
	    cpu_to_le16(sp->fcport->loop_id << 8);
	mbx->mb2 = cpu_to_le16(sp->fcport->d_id.b.domain);
	mbx->mb3 = cpu_to_le16(sp->fcport->d_id.b.area << 8 |
	    sp->fcport->d_id.b.al_pa);
	mbx->mb9 = cpu_to_le16(sp->vha->vp_idx);
	/* Implicit: mbx->mbx10 = 0. */
}