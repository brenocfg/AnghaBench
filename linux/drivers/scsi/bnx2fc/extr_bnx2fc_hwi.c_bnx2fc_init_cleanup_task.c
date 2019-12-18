#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_15__ {int rx_flags; } ;
struct TYPE_14__ {int init_flags; } ;
struct TYPE_16__ {TYPE_7__ var_ctx; TYPE_6__ const_ctx; } ;
struct TYPE_12__ {int init_flags; int tx_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  cleaned_task_id; } ;
struct TYPE_10__ {TYPE_1__ ctx; } ;
struct TYPE_11__ {TYPE_2__ cleanup; } ;
struct TYPE_13__ {TYPE_4__ const_ctx; TYPE_3__ union_ctx; } ;
struct fcoe_task_ctx_entry {TYPE_8__ rxwr_txrd; TYPE_5__ txwr_rxrd; } ;
struct bnx2fc_rport {int context_id; scalar_t__ dev_type; } ;
struct bnx2fc_cmd {struct bnx2fc_rport* tgt; } ;

/* Variables and functions */
 int FCOE_TASK_CLASS_TYPE_3 ; 
 int FCOE_TASK_DEV_TYPE_DISK ; 
 int FCOE_TASK_DEV_TYPE_TAPE ; 
 int FCOE_TASK_TX_STATE_EXCHANGE_CLEANUP ; 
 int FCOE_TASK_TYPE_EXCHANGE_CLEANUP ; 
 int FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT ; 
 int FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT ; 
 int FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT ; 
 int FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT ; 
 int FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT ; 
 int FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT ; 
 scalar_t__ TYPE_TAPE ; 
 int /*<<< orphan*/  memset (struct fcoe_task_ctx_entry*,int /*<<< orphan*/ ,int) ; 

void bnx2fc_init_cleanup_task(struct bnx2fc_cmd *io_req,
			      struct fcoe_task_ctx_entry *task,
			      u16 orig_xid)
{
	u8 task_type = FCOE_TASK_TYPE_EXCHANGE_CLEANUP;
	struct bnx2fc_rport *tgt = io_req->tgt;
	u32 context_id = tgt->context_id;

	memset(task, 0, sizeof(struct fcoe_task_ctx_entry));

	/* Tx Write Rx Read */
	/* init flags */
	task->txwr_rxrd.const_ctx.init_flags = task_type <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT;
	task->txwr_rxrd.const_ctx.init_flags |= FCOE_TASK_CLASS_TYPE_3 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT;
	if (tgt->dev_type == TYPE_TAPE)
		task->txwr_rxrd.const_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_TAPE <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	else
		task->txwr_rxrd.const_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_DISK <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	task->txwr_rxrd.union_ctx.cleanup.ctx.cleaned_task_id = orig_xid;

	/* Tx flags */
	task->txwr_rxrd.const_ctx.tx_flags =
				FCOE_TASK_TX_STATE_EXCHANGE_CLEANUP <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT;

	/* Rx Read Tx Write */
	task->rxwr_txrd.const_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;
	task->rxwr_txrd.var_ctx.rx_flags |= 1 <<
				FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT;
}