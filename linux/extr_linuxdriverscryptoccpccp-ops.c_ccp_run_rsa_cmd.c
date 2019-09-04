#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct ccp_rsa_engine {int key_size; int /*<<< orphan*/  mod_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; int /*<<< orphan*/  mod; int /*<<< orphan*/  exp_len; int /*<<< orphan*/  exp; } ;
struct TYPE_19__ {int mod_size; unsigned int input_len; } ;
struct TYPE_20__ {TYPE_12__ rsa; } ;
struct TYPE_32__ {unsigned int length; scalar_t__ offset; int /*<<< orphan*/  address; } ;
struct TYPE_17__ {TYPE_9__ dma; } ;
struct TYPE_18__ {TYPE_10__ u; } ;
struct TYPE_28__ {unsigned int length; scalar_t__ offset; int /*<<< orphan*/  address; } ;
struct TYPE_29__ {TYPE_5__ dma; } ;
struct TYPE_30__ {TYPE_6__ u; } ;
struct TYPE_25__ {scalar_t__ offset; int /*<<< orphan*/  address; } ;
struct TYPE_26__ {TYPE_2__ dma; } ;
struct TYPE_27__ {TYPE_3__ u; } ;
struct ccp_op {int soc; scalar_t__ sb_key; TYPE_13__ u; TYPE_11__ dst; TYPE_7__ src; TYPE_4__ exp; int /*<<< orphan*/  jobid; struct ccp_cmd_queue* cmd_q; } ;
struct TYPE_31__ {int /*<<< orphan*/  address; } ;
struct ccp_dm_workarea {TYPE_8__ dma; } ;
struct ccp_cmd_queue {TYPE_16__* ccp; int /*<<< orphan*/  cmd_error; scalar_t__ sb_key; } ;
struct TYPE_24__ {struct ccp_rsa_engine rsa; } ;
struct ccp_cmd {int /*<<< orphan*/  engine_error; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  op ;
struct TYPE_23__ {TYPE_15__* vdata; } ;
struct TYPE_22__ {int rsamax; scalar_t__ version; TYPE_14__* perform; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* sbfree ) (struct ccp_cmd_queue*,scalar_t__,unsigned int) ;int /*<<< orphan*/  (* rsa ) (struct ccp_op*) ;scalar_t__ (* sballoc ) (struct ccp_cmd_queue*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_NEW_JOBID (TYPE_16__*) ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_NOOP ; 
 unsigned int CCP_SB_BYTES ; 
 scalar_t__ CCP_VERSION (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 int ccp_copy_to_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_dm_free (struct ccp_dm_workarea*) ; 
 int ccp_init_dm_workarea (struct ccp_dm_workarea*,struct ccp_cmd_queue*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_reverse_get_dm_area (struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccp_reverse_set_dm_area (struct ccp_dm_workarea*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ccp_op*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ccp_cmd_queue*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct ccp_op*) ; 
 int /*<<< orphan*/  stub3 (struct ccp_cmd_queue*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int ccp_run_rsa_cmd(struct ccp_cmd_queue *cmd_q, struct ccp_cmd *cmd)
{
	struct ccp_rsa_engine *rsa = &cmd->u.rsa;
	struct ccp_dm_workarea exp, src, dst;
	struct ccp_op op;
	unsigned int sb_count, i_len, o_len;
	int ret;

	/* Check against the maximum allowable size, in bits */
	if (rsa->key_size > cmd_q->ccp->vdata->rsamax)
		return -EINVAL;

	if (!rsa->exp || !rsa->mod || !rsa->src || !rsa->dst)
		return -EINVAL;

	memset(&op, 0, sizeof(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);

	/* The RSA modulus must precede the message being acted upon, so
	 * it must be copied to a DMA area where the message and the
	 * modulus can be concatenated.  Therefore the input buffer
	 * length required is twice the output buffer length (which
	 * must be a multiple of 256-bits).  Compute o_len, i_len in bytes.
	 * Buffer sizes must be a multiple of 32 bytes; rounding up may be
	 * required.
	 */
	o_len = 32 * ((rsa->key_size + 255) / 256);
	i_len = o_len * 2;

	sb_count = 0;
	if (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) {
		/* sb_count is the number of storage block slots required
		 * for the modulus.
		 */
		sb_count = o_len / CCP_SB_BYTES;
		op.sb_key = cmd_q->ccp->vdata->perform->sballoc(cmd_q,
								sb_count);
		if (!op.sb_key)
			return -EIO;
	} else {
		/* A version 5 device allows a modulus size that will not fit
		 * in the LSB, so the command will transfer it from memory.
		 * Set the sb key to the default, even though it's not used.
		 */
		op.sb_key = cmd_q->sb_key;
	}

	/* The RSA exponent must be in little endian format. Reverse its
	 * byte order.
	 */
	ret = ccp_init_dm_workarea(&exp, cmd_q, o_len, DMA_TO_DEVICE);
	if (ret)
		goto e_sb;

	ret = ccp_reverse_set_dm_area(&exp, 0, rsa->exp, 0, rsa->exp_len);
	if (ret)
		goto e_exp;

	if (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) {
		/* Copy the exponent to the local storage block, using
		 * as many 32-byte blocks as were allocated above. It's
		 * already little endian, so no further change is required.
		 */
		ret = ccp_copy_to_sb(cmd_q, &exp, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_exp;
		}
	} else {
		/* The exponent can be retrieved from memory via DMA. */
		op.exp.u.dma.address = exp.dma.address;
		op.exp.u.dma.offset = 0;
	}

	/* Concatenate the modulus and the message. Both the modulus and
	 * the operands must be in little endian format.  Since the input
	 * is in big endian format it must be converted.
	 */
	ret = ccp_init_dm_workarea(&src, cmd_q, i_len, DMA_TO_DEVICE);
	if (ret)
		goto e_exp;

	ret = ccp_reverse_set_dm_area(&src, 0, rsa->mod, 0, rsa->mod_len);
	if (ret)
		goto e_src;
	ret = ccp_reverse_set_dm_area(&src, o_len, rsa->src, 0, rsa->src_len);
	if (ret)
		goto e_src;

	/* Prepare the output area for the operation */
	ret = ccp_init_dm_workarea(&dst, cmd_q, o_len, DMA_FROM_DEVICE);
	if (ret)
		goto e_src;

	op.soc = 1;
	op.src.u.dma.address = src.dma.address;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = i_len;
	op.dst.u.dma.address = dst.dma.address;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = o_len;

	op.u.rsa.mod_size = rsa->key_size;
	op.u.rsa.input_len = i_len;

	ret = cmd_q->ccp->vdata->perform->rsa(&op);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_dst;
	}

	ccp_reverse_get_dm_area(&dst, 0, rsa->dst, 0, rsa->mod_len);

e_dst:
	ccp_dm_free(&dst);

e_src:
	ccp_dm_free(&src);

e_exp:
	ccp_dm_free(&exp);

e_sb:
	if (sb_count)
		cmd_q->ccp->vdata->perform->sbfree(cmd_q, op.sb_key, sb_count);

	return ret;
}