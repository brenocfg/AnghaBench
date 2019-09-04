#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct ccp_passthru_nomap_engine {int src_len; scalar_t__ bit_mod; scalar_t__ mask_len; scalar_t__ dst_dma; scalar_t__ src_dma; scalar_t__ mask; int /*<<< orphan*/  final; } ;
struct TYPE_19__ {int length; scalar_t__ offset; scalar_t__ address; } ;
struct TYPE_20__ {TYPE_6__ dma; } ;
struct TYPE_21__ {TYPE_7__ u; void* type; } ;
struct TYPE_16__ {int length; scalar_t__ offset; scalar_t__ address; } ;
struct TYPE_17__ {TYPE_3__ dma; } ;
struct TYPE_18__ {TYPE_4__ u; void* type; } ;
struct ccp_op {int eom; int soc; TYPE_8__ dst; TYPE_5__ src; int /*<<< orphan*/  sb_key; int /*<<< orphan*/  jobid; struct ccp_cmd_queue* cmd_q; } ;
struct TYPE_15__ {scalar_t__ length; scalar_t__ address; } ;
struct ccp_dm_workarea {scalar_t__ length; TYPE_2__ dma; } ;
struct ccp_cmd_queue {int /*<<< orphan*/  cmd_error; TYPE_11__* ccp; int /*<<< orphan*/  sb_key; } ;
struct TYPE_14__ {struct ccp_passthru_nomap_engine passthru_nomap; } ;
struct ccp_cmd {int /*<<< orphan*/  engine_error; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  op ;
struct TYPE_22__ {int (* passthru ) (struct ccp_op*) ;} ;
struct TYPE_13__ {TYPE_10__* vdata; } ;
struct TYPE_12__ {TYPE_9__* perform; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 void* CCP_MEMTYPE_SYSTEM ; 
 int /*<<< orphan*/  CCP_NEW_JOBID (TYPE_11__*) ; 
 scalar_t__ CCP_PASSTHRU_BITWISE_NOOP ; 
 int CCP_PASSTHRU_BLOCKSIZE ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_NOOP ; 
 scalar_t__ CCP_PASSTHRU_MASKSIZE ; 
 int CCP_PASSTHRU_SB_COUNT ; 
 int EINVAL ; 
 int ccp_copy_to_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ccp_op*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ccp_op*) ; 

__attribute__((used)) static int ccp_run_passthru_nomap_cmd(struct ccp_cmd_queue *cmd_q,
				      struct ccp_cmd *cmd)
{
	struct ccp_passthru_nomap_engine *pt = &cmd->u.passthru_nomap;
	struct ccp_dm_workarea mask;
	struct ccp_op op;
	int ret;

	if (!pt->final && (pt->src_len & (CCP_PASSTHRU_BLOCKSIZE - 1)))
		return -EINVAL;

	if (!pt->src_dma || !pt->dst_dma)
		return -EINVAL;

	if (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) {
		if (pt->mask_len != CCP_PASSTHRU_MASKSIZE)
			return -EINVAL;
		if (!pt->mask)
			return -EINVAL;
	}

	BUILD_BUG_ON(CCP_PASSTHRU_SB_COUNT != 1);

	memset(&op, 0, sizeof(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	if (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP) {
		/* Load the mask */
		op.sb_key = cmd_q->sb_key;

		mask.length = pt->mask_len;
		mask.dma.address = pt->mask;
		mask.dma.length = pt->mask_len;

		ret = ccp_copy_to_sb(cmd_q, &mask, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			return ret;
		}
	}

	/* Send data to the CCP Passthru engine */
	op.eom = 1;
	op.soc = 1;

	op.src.type = CCP_MEMTYPE_SYSTEM;
	op.src.u.dma.address = pt->src_dma;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = pt->src_len;

	op.dst.type = CCP_MEMTYPE_SYSTEM;
	op.dst.u.dma.address = pt->dst_dma;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = pt->src_len;

	ret = cmd_q->ccp->vdata->perform->passthru(&op);
	if (ret)
		cmd->engine_error = cmd_q->cmd_error;

	return ret;
}