#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct ccp_passthru_engine {int src_len; scalar_t__ bit_mod; scalar_t__ mask_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  mask; int /*<<< orphan*/  final; } ;
struct TYPE_22__ {int /*<<< orphan*/  length; scalar_t__ offset; void* address; } ;
struct TYPE_23__ {TYPE_5__ dma; } ;
struct TYPE_24__ {TYPE_6__ u; void* type; } ;
struct TYPE_19__ {scalar_t__ offset; int /*<<< orphan*/  length; void* address; } ;
struct TYPE_20__ {TYPE_2__ dma; } ;
struct TYPE_21__ {TYPE_3__ u; void* type; } ;
struct ccp_op {int eom; int soc; TYPE_7__ src; TYPE_4__ dst; int /*<<< orphan*/  sb_key; int /*<<< orphan*/  jobid; struct ccp_cmd_queue* cmd_q; } ;
struct ccp_dm_workarea {int dummy; } ;
struct TYPE_15__ {scalar_t__ sg_used; unsigned int dma_count; TYPE_11__* sg; } ;
struct ccp_data {TYPE_10__ sg_wa; } ;
struct ccp_cmd_queue {int /*<<< orphan*/  cmd_error; TYPE_14__* ccp; int /*<<< orphan*/  sb_key; } ;
struct TYPE_18__ {struct ccp_passthru_engine passthru; } ;
struct ccp_cmd {int /*<<< orphan*/  engine_error; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  op ;
struct TYPE_26__ {TYPE_8__* perform; } ;
struct TYPE_25__ {int (* passthru ) (struct ccp_op*) ;} ;
struct TYPE_17__ {TYPE_9__* vdata; } ;
struct TYPE_16__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 void* CCP_MEMTYPE_SYSTEM ; 
 int /*<<< orphan*/  CCP_NEW_JOBID (TYPE_14__*) ; 
 scalar_t__ CCP_PASSTHRU_BITWISE_NOOP ; 
 int CCP_PASSTHRU_BLOCKSIZE ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_NOOP ; 
 scalar_t__ CCP_PASSTHRU_MASKSIZE ; 
 int CCP_PASSTHRU_SB_COUNT ; 
 int CCP_SB_BYTES ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ccp_copy_to_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_dm_free (struct ccp_dm_workarea*) ; 
 int /*<<< orphan*/  ccp_free_data (struct ccp_data*,struct ccp_cmd_queue*) ; 
 int ccp_init_data (struct ccp_data*,struct ccp_cmd_queue*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int ccp_init_dm_workarea (struct ccp_dm_workarea*,struct ccp_cmd_queue*,int,int /*<<< orphan*/ ) ; 
 int ccp_set_dm_area (struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ccp_op*,int /*<<< orphan*/ ,int) ; 
 void* sg_dma_address (TYPE_11__*) ; 
 int /*<<< orphan*/  sg_dma_len (TYPE_11__*) ; 
 void* sg_next (TYPE_11__*) ; 
 scalar_t__ sg_virt (int /*<<< orphan*/ ) ; 
 int stub1 (struct ccp_op*) ; 

__attribute__((used)) static int ccp_run_passthru_cmd(struct ccp_cmd_queue *cmd_q,
				struct ccp_cmd *cmd)
{
	struct ccp_passthru_engine *pt = &cmd->u.passthru;
	struct ccp_dm_workarea mask;
	struct ccp_data src, dst;
	struct ccp_op op;
	bool in_place = false;
	unsigned int i;
	int ret = 0;

	if (!pt->final && (pt->src_len & (CCP_PASSTHRU_BLOCKSIZE - 1)))
		return -EINVAL;

	if (!pt->src || !pt->dst)
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

		ret = ccp_init_dm_workarea(&mask, cmd_q,
					   CCP_PASSTHRU_SB_COUNT *
					   CCP_SB_BYTES,
					   DMA_TO_DEVICE);
		if (ret)
			return ret;

		ret = ccp_set_dm_area(&mask, 0, pt->mask, 0, pt->mask_len);
		if (ret)
			goto e_mask;
		ret = ccp_copy_to_sb(cmd_q, &mask, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_mask;
		}
	}

	/* Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIDIRECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	if (sg_virt(pt->src) == sg_virt(pt->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, pt->src, pt->src_len,
			    CCP_PASSTHRU_MASKSIZE,
			    in_place ? DMA_BIDIRECTIONAL : DMA_TO_DEVICE);
	if (ret)
		goto e_mask;

	if (in_place) {
		dst = src;
	} else {
		ret = ccp_init_data(&dst, cmd_q, pt->dst, pt->src_len,
				    CCP_PASSTHRU_MASKSIZE, DMA_FROM_DEVICE);
		if (ret)
			goto e_src;
	}

	/* Send data to the CCP Passthru engine
	 *   Because the CCP engine works on a single source and destination
	 *   dma address at a time, each entry in the source scatterlist
	 *   (after the dma_map_sg call) must be less than or equal to the
	 *   (remaining) length in the destination scatterlist entry and the
	 *   length must be a multiple of CCP_PASSTHRU_BLOCKSIZE
	 */
	dst.sg_wa.sg_used = 0;
	for (i = 1; i <= src.sg_wa.dma_count; i++) {
		if (!dst.sg_wa.sg ||
		    (dst.sg_wa.sg->length < src.sg_wa.sg->length)) {
			ret = -EINVAL;
			goto e_dst;
		}

		if (i == src.sg_wa.dma_count) {
			op.eom = 1;
			op.soc = 1;
		}

		op.src.type = CCP_MEMTYPE_SYSTEM;
		op.src.u.dma.address = sg_dma_address(src.sg_wa.sg);
		op.src.u.dma.offset = 0;
		op.src.u.dma.length = sg_dma_len(src.sg_wa.sg);

		op.dst.type = CCP_MEMTYPE_SYSTEM;
		op.dst.u.dma.address = sg_dma_address(dst.sg_wa.sg);
		op.dst.u.dma.offset = dst.sg_wa.sg_used;
		op.dst.u.dma.length = op.src.u.dma.length;

		ret = cmd_q->ccp->vdata->perform->passthru(&op);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_dst;
		}

		dst.sg_wa.sg_used += src.sg_wa.sg->length;
		if (dst.sg_wa.sg_used == dst.sg_wa.sg->length) {
			dst.sg_wa.sg = sg_next(dst.sg_wa.sg);
			dst.sg_wa.sg_used = 0;
		}
		src.sg_wa.sg = sg_next(src.sg_wa.sg);
	}

e_dst:
	if (!in_place)
		ccp_free_data(&dst, cmd_q);

e_src:
	ccp_free_data(&src, cmd_q);

e_mask:
	if (pt->bit_mod != CCP_PASSTHRU_BITWISE_NOOP)
		ccp_dm_free(&mask);

	return ret;
}