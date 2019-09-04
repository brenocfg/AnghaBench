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
struct TYPE_9__ {int /*<<< orphan*/  action; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_2__ aes; } ;
struct ccp_op {int init; int eom; int /*<<< orphan*/  sb_ctx; int /*<<< orphan*/  jobid; int /*<<< orphan*/  sb_key; TYPE_3__ u; struct ccp_cmd_queue* cmd_q; } ;
struct ccp_dm_workarea {int dummy; } ;
struct TYPE_11__ {scalar_t__ bytes_left; } ;
struct ccp_data {TYPE_4__ sg_wa; } ;
struct ccp_cmd_queue {int /*<<< orphan*/  cmd_error; TYPE_7__* ccp; int /*<<< orphan*/  sb_ctx; int /*<<< orphan*/  sb_key; } ;
struct ccp_aes_engine {int key_len; int src_len; int iv_len; int cmac_key_len; int /*<<< orphan*/  iv; int /*<<< orphan*/  cmac_key; scalar_t__ cmac_final; int /*<<< orphan*/  src; int /*<<< orphan*/  key; int /*<<< orphan*/  action; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {struct ccp_aes_engine aes; } ;
struct ccp_cmd {int /*<<< orphan*/  engine_error; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  op ;
struct TYPE_14__ {TYPE_6__* vdata; } ;
struct TYPE_13__ {TYPE_5__* perform; } ;
struct TYPE_12__ {int (* aes ) (struct ccp_op*) ;} ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int AES_KEYSIZE_128 ; 
 int AES_KEYSIZE_192 ; 
 int AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int CCP_AES_CTX_SB_COUNT ; 
 int CCP_AES_KEY_SB_COUNT ; 
 int /*<<< orphan*/  CCP_NEW_JOBID (TYPE_7__*) ; 
 int /*<<< orphan*/  CCP_PASSTHRU_BYTESWAP_256BIT ; 
 int CCP_SB_BYTES ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 int ccp_copy_from_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccp_copy_to_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_dm_free (struct ccp_dm_workarea*) ; 
 int /*<<< orphan*/  ccp_free_data (struct ccp_data*,struct ccp_cmd_queue*) ; 
 int /*<<< orphan*/  ccp_get_dm_area (struct ccp_dm_workarea*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ccp_init_data (struct ccp_data*,struct ccp_cmd_queue*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int ccp_init_dm_workarea (struct ccp_dm_workarea*,struct ccp_cmd_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_prepare_data (struct ccp_data*,int /*<<< orphan*/ *,struct ccp_op*,int,int) ; 
 int /*<<< orphan*/  ccp_process_data (struct ccp_data*,int /*<<< orphan*/ *,struct ccp_op*) ; 
 int ccp_set_dm_area (struct ccp_dm_workarea*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ccp_op*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ccp_op*) ; 

__attribute__((used)) static int ccp_run_aes_cmac_cmd(struct ccp_cmd_queue *cmd_q,
				struct ccp_cmd *cmd)
{
	struct ccp_aes_engine *aes = &cmd->u.aes;
	struct ccp_dm_workarea key, ctx;
	struct ccp_data src;
	struct ccp_op op;
	unsigned int dm_offset;
	int ret;

	if (!((aes->key_len == AES_KEYSIZE_128) ||
	      (aes->key_len == AES_KEYSIZE_192) ||
	      (aes->key_len == AES_KEYSIZE_256)))
		return -EINVAL;

	if (aes->src_len & (AES_BLOCK_SIZE - 1))
		return -EINVAL;

	if (aes->iv_len != AES_BLOCK_SIZE)
		return -EINVAL;

	if (!aes->key || !aes->iv || !aes->src)
		return -EINVAL;

	if (aes->cmac_final) {
		if (aes->cmac_key_len != AES_BLOCK_SIZE)
			return -EINVAL;

		if (!aes->cmac_key)
			return -EINVAL;
	}

	BUILD_BUG_ON(CCP_AES_KEY_SB_COUNT != 1);
	BUILD_BUG_ON(CCP_AES_CTX_SB_COUNT != 1);

	ret = -EIO;
	memset(&op, 0, sizeof(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);
	op.sb_key = cmd_q->sb_key;
	op.sb_ctx = cmd_q->sb_ctx;
	op.init = 1;
	op.u.aes.type = aes->type;
	op.u.aes.mode = aes->mode;
	op.u.aes.action = aes->action;

	/* All supported key sizes fit in a single (32-byte) SB entry
	 * and must be in little endian format. Use the 256-bit byte
	 * swap passthru option to convert from big endian to little
	 * endian.
	 */
	ret = ccp_init_dm_workarea(&key, cmd_q,
				   CCP_AES_KEY_SB_COUNT * CCP_SB_BYTES,
				   DMA_TO_DEVICE);
	if (ret)
		return ret;

	dm_offset = CCP_SB_BYTES - aes->key_len;
	ret = ccp_set_dm_area(&key, dm_offset, aes->key, 0, aes->key_len);
	if (ret)
		goto e_key;
	ret = ccp_copy_to_sb(cmd_q, &key, op.jobid, op.sb_key,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_key;
	}

	/* The AES context fits in a single (32-byte) SB entry and
	 * must be in little endian format. Use the 256-bit byte swap
	 * passthru option to convert from big endian to little endian.
	 */
	ret = ccp_init_dm_workarea(&ctx, cmd_q,
				   CCP_AES_CTX_SB_COUNT * CCP_SB_BYTES,
				   DMA_BIDIRECTIONAL);
	if (ret)
		goto e_key;

	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ret = ccp_set_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);
	if (ret)
		goto e_ctx;
	ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			     CCP_PASSTHRU_BYTESWAP_256BIT);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_ctx;
	}

	/* Send data to the CCP AES engine */
	ret = ccp_init_data(&src, cmd_q, aes->src, aes->src_len,
			    AES_BLOCK_SIZE, DMA_TO_DEVICE);
	if (ret)
		goto e_ctx;

	while (src.sg_wa.bytes_left) {
		ccp_prepare_data(&src, NULL, &op, AES_BLOCK_SIZE, true);
		if (aes->cmac_final && !src.sg_wa.bytes_left) {
			op.eom = 1;

			/* Push the K1/K2 key to the CCP now */
			ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid,
					       op.sb_ctx,
					       CCP_PASSTHRU_BYTESWAP_256BIT);
			if (ret) {
				cmd->engine_error = cmd_q->cmd_error;
				goto e_src;
			}

			ret = ccp_set_dm_area(&ctx, 0, aes->cmac_key, 0,
					      aes->cmac_key_len);
			if (ret)
				goto e_src;
			ret = ccp_copy_to_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
					     CCP_PASSTHRU_BYTESWAP_256BIT);
			if (ret) {
				cmd->engine_error = cmd_q->cmd_error;
				goto e_src;
			}
		}

		ret = cmd_q->ccp->vdata->perform->aes(&op);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_src;
		}

		ccp_process_data(&src, NULL, &op);
	}

	/* Retrieve the AES context - convert from LE to BE using
	 * 32-byte (256-bit) byteswapping
	 */
	ret = ccp_copy_from_sb(cmd_q, &ctx, op.jobid, op.sb_ctx,
			       CCP_PASSTHRU_BYTESWAP_256BIT);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_src;
	}

	/* ...but we only need AES_BLOCK_SIZE bytes */
	dm_offset = CCP_SB_BYTES - AES_BLOCK_SIZE;
	ccp_get_dm_area(&ctx, dm_offset, aes->iv, 0, aes->iv_len);

e_src:
	ccp_free_data(&src, cmd_q);

e_ctx:
	ccp_dm_free(&ctx);

e_key:
	ccp_dm_free(&key);

	return ret;
}