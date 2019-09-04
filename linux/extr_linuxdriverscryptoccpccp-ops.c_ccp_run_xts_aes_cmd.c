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
struct ccp_xts_aes_engine {int unit_size; unsigned int key_len; int src_len; int iv_len; int /*<<< orphan*/  iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  key; int /*<<< orphan*/  action; int /*<<< orphan*/  final; } ;
struct TYPE_11__ {int type; int unit_size; int /*<<< orphan*/  action; } ;
struct TYPE_12__ {TYPE_4__ xts; } ;
struct ccp_op {int init; int eom; int /*<<< orphan*/  sb_ctx; int /*<<< orphan*/  jobid; int /*<<< orphan*/  sb_key; TYPE_5__ u; struct ccp_cmd_queue* cmd_q; } ;
struct ccp_dm_workarea {int dummy; } ;
struct TYPE_8__ {scalar_t__ bytes_left; } ;
struct ccp_data {TYPE_1__ sg_wa; } ;
struct ccp_cmd_queue {int /*<<< orphan*/  cmd_error; TYPE_7__* ccp; int /*<<< orphan*/  sb_ctx; int /*<<< orphan*/  sb_key; } ;
struct TYPE_10__ {struct ccp_xts_aes_engine xts; } ;
struct ccp_cmd {int /*<<< orphan*/  engine_error; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  op ;
typedef  enum ccp_aes_type { ____Placeholder_ccp_aes_type } ccp_aes_type ;
struct TYPE_14__ {TYPE_6__* vdata; } ;
struct TYPE_13__ {scalar_t__ version; TYPE_2__* perform; } ;
struct TYPE_9__ {int (* xts_aes ) (struct ccp_op*) ;} ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 unsigned int AES_KEYSIZE_128 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int CCP5_XTS_AES_KEY_SB_COUNT ; 
 int CCP_AES_TYPE_128 ; 
 int CCP_AES_TYPE_256 ; 
 int /*<<< orphan*/  CCP_NEW_JOBID (TYPE_7__*) ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_256BIT ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_NOOP ; 
 unsigned int CCP_SB_BYTES ; 
 scalar_t__ CCP_VERSION (int,int /*<<< orphan*/ ) ; 
 int CCP_XTS_AES_CTX_SB_COUNT ; 
 int CCP_XTS_AES_KEY_SB_COUNT ; 
#define  CCP_XTS_AES_UNIT_SIZE_1024 132 
#define  CCP_XTS_AES_UNIT_SIZE_16 131 
#define  CCP_XTS_AES_UNIT_SIZE_2048 130 
#define  CCP_XTS_AES_UNIT_SIZE_4096 129 
#define  CCP_XTS_AES_UNIT_SIZE_512 128 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 int ccp_copy_from_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccp_copy_to_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_dm_free (struct ccp_dm_workarea*) ; 
 int /*<<< orphan*/  ccp_free_data (struct ccp_data*,struct ccp_cmd_queue*) ; 
 int /*<<< orphan*/  ccp_get_dm_area (struct ccp_dm_workarea*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ccp_init_data (struct ccp_data*,struct ccp_cmd_queue*,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int ccp_init_dm_workarea (struct ccp_dm_workarea*,struct ccp_cmd_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_prepare_data (struct ccp_data*,struct ccp_data*,struct ccp_op*,unsigned int,int) ; 
 int /*<<< orphan*/  ccp_process_data (struct ccp_data*,struct ccp_data*,struct ccp_op*) ; 
 int ccp_set_dm_area (struct ccp_dm_workarea*,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (struct ccp_op*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sg_virt (int /*<<< orphan*/ ) ; 
 int stub1 (struct ccp_op*) ; 

__attribute__((used)) static int ccp_run_xts_aes_cmd(struct ccp_cmd_queue *cmd_q,
			       struct ccp_cmd *cmd)
{
	struct ccp_xts_aes_engine *xts = &cmd->u.xts;
	struct ccp_dm_workarea key, ctx;
	struct ccp_data src, dst;
	struct ccp_op op;
	unsigned int unit_size, dm_offset;
	bool in_place = false;
	unsigned int sb_count;
	enum ccp_aes_type aestype;
	int ret;

	switch (xts->unit_size) {
	case CCP_XTS_AES_UNIT_SIZE_16:
		unit_size = 16;
		break;
	case CCP_XTS_AES_UNIT_SIZE_512:
		unit_size = 512;
		break;
	case CCP_XTS_AES_UNIT_SIZE_1024:
		unit_size = 1024;
		break;
	case CCP_XTS_AES_UNIT_SIZE_2048:
		unit_size = 2048;
		break;
	case CCP_XTS_AES_UNIT_SIZE_4096:
		unit_size = 4096;
		break;

	default:
		return -EINVAL;
	}

	if (xts->key_len == AES_KEYSIZE_128)
		aestype = CCP_AES_TYPE_128;
	else if (xts->key_len == AES_KEYSIZE_256)
		aestype = CCP_AES_TYPE_256;
	else
		return -EINVAL;

	if (!xts->final && (xts->src_len & (AES_BLOCK_SIZE - 1)))
		return -EINVAL;

	if (xts->iv_len != AES_BLOCK_SIZE)
		return -EINVAL;

	if (!xts->key || !xts->iv || !xts->src || !xts->dst)
		return -EINVAL;

	BUILD_BUG_ON(CCP_XTS_AES_KEY_SB_COUNT != 1);
	BUILD_BUG_ON(CCP_XTS_AES_CTX_SB_COUNT != 1);

	ret = -EIO;
	memset(&op, 0, sizeof(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;
	op.sb_ctx = cmd_q->sb_ctx;
	op.init = 1;
	op.u.xts.type = aestype;
	op.u.xts.action = xts->action;
	op.u.xts.unit_size = xts->unit_size;

	/* A version 3 device only supports 128-bit keys, which fits into a
	 * single SB entry. A version 5 device uses a 512-bit vector, so two
	 * SB entries.
	 */
	if (cmd_q->ccp->vdata->version == CCP_VERSION(3, 0))
		sb_count = CCP_XTS_AES_KEY_SB_COUNT;
	else
		sb_count = CCP5_XTS_AES_KEY_SB_COUNT;
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   sb_count * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	if (ret)
		return ret;

	if (cmd_q->ccp->vdata->version == CCP_VERSION(3, 0)) {
		/* All supported key sizes must be in little endian format.
		 * Use the 256-bit byte swap passthru option to convert from
		 * big endian to little endian.
		 */
		dm_offset = CCP_SB_BYTES - AES_KEYSIZE_128;
		ret = ccp_set_dm_area(&key, dm_offset, xts->key, 0, xts->key_len);
		if (ret)
			goto e_key;
		ret = ccp_set_dm_area(&key, 0, xts->key, xts->key_len, xts->key_len);
		if (ret)
			goto e_key;
	} else {
		/* Version 5 CCPs use a 512-bit space for the key: each portion
		 * occupies 256 bits, or one entire slot, and is zero-padded.
		 */
		unsigned int pad;

		dm_offset = CCP_SB_BYTES;
		pad = dm_offset - xts->key_len;
		ret = ccp_set_dm_area(&key, pad, xts->key, 0, xts->key_len);
		if (ret)
			goto e_key;
		ret = ccp_set_dm_area(&key, dm_offset + pad, xts->key,
				      xts->key_len, xts->key_len);
		if (ret)
			goto e_key;
	}
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_key;
	}

	/* The AES context fits in a single (32-byte) SB entry and
	 * for XTS is already in little endian format so no byte swapping
	 * is needed.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_XTS_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIDIRECTIONAL);
	if (ret)
		goto e_key;

	ret = ccp_set_dm_area(&ctx, 0, xts->iv, 0, xts->iv_len);
	if (ret)
		goto e_ctx;
	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_NOOP);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_ctx;
	}

	/* Prepare the input and output data workareas. For in-place
	 * operations we need to set the dma direction to BIDIRECTIONAL
	 * and copy the src workarea to the dst workarea.
	 */
	if (sg_virt(xts->src) == sg_virt(xts->dst))
		in_place = true;

	ret = ccp_init_data(&src, cmd_q, xts->src, xts->src_len,
			    unit_size,
			    in_place ? DMA_BIDIRECTIONAL : DMA_TO_DEVICE);
	if (ret)
		goto e_ctx;

	if (in_place) {
		dst = src;
	} else {
		ret = ccp_init_data(&dst, cmd_q, xts->dst, xts->src_len,
				    unit_size, DMA_FROM_DEVICE);
		if (ret)
			goto e_src;
	}

	/* Send data to the CCP AES engine */
	while (src.sg_wa.bytes_left) {
		ccp_prepare_data(&src, &dst, &op, unit_size, true);
		if (!src.sg_wa.bytes_left)
			op.eom = 1;

		ret = cmd_q->ccp->vdata->perform->xts_aes(&op);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_dst;
		}

		ccp_process_data(&src, &dst, &op);
	}

	/* Retrieve the AES context - convert from LE to BE using
	 * 32-byte (256-bit) byteswapping
	 */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_dst;
	}

	/* ...but we only need AES_BLOCK_SIZE bytes */
	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ccp_get_dm_area(&ctx, dm_offset, xts->iv, 0, xts->iv_len);

e_dst:
	if (!in_place)
		ccp_free_data(&dst, cmd_q);

e_src:
	ccp_free_data(&src, cmd_q);

e_ctx:
	ccp_dm_free(&ctx);

e_key:
	ccp_dm_free(&key);

	return ret;
}