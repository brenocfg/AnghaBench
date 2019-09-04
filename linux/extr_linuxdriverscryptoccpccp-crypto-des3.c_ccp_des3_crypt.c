#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_10__ {scalar_t__ mode; unsigned int iv_len; int src_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; struct scatterlist* iv; scalar_t__ key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/  action; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_3__ des3; } ;
struct TYPE_12__ {TYPE_4__ u; int /*<<< orphan*/  engine; int /*<<< orphan*/  entry; } ;
struct ccp_des3_req_ctx {TYPE_5__ cmd; int /*<<< orphan*/  iv; struct scatterlist iv_sg; } ;
struct TYPE_8__ {scalar_t__ mode; scalar_t__ key_len; int /*<<< orphan*/  key_sg; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_1__ des3; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {int nbytes; TYPE_6__ base; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_DES3_ACTION_DECRYPT ; 
 int /*<<< orphan*/  CCP_DES3_ACTION_ENCRYPT ; 
 scalar_t__ CCP_DES3_MODE_CBC ; 
 scalar_t__ CCP_DES3_MODE_ECB ; 
 int /*<<< orphan*/  CCP_ENGINE_DES3 ; 
 int DES3_EDE_BLOCK_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ccp_des3_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int ccp_crypto_enqueue_request (TYPE_6__*,TYPE_5__*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ccp_des3_crypt(struct ablkcipher_request *req, bool encrypt)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct ccp_des3_req_ctx *rctx = ablkcipher_request_ctx(req);
	struct scatterlist *iv_sg = NULL;
	unsigned int iv_len = 0;
	int ret;

	if (!ctx->u.des3.key_len)
		return -EINVAL;

	if (((ctx->u.des3.mode == CCP_DES3_MODE_ECB) ||
	     (ctx->u.des3.mode == CCP_DES3_MODE_CBC)) &&
	    (req->nbytes & (DES3_EDE_BLOCK_SIZE - 1)))
		return -EINVAL;

	if (ctx->u.des3.mode != CCP_DES3_MODE_ECB) {
		if (!req->info)
			return -EINVAL;

		memcpy(rctx->iv, req->info, DES3_EDE_BLOCK_SIZE);
		iv_sg = &rctx->iv_sg;
		iv_len = DES3_EDE_BLOCK_SIZE;
		sg_init_one(iv_sg, rctx->iv, iv_len);
	}

	memset(&rctx->cmd, 0, sizeof(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_DES3;
	rctx->cmd.u.des3.type = ctx->u.des3.type;
	rctx->cmd.u.des3.mode = ctx->u.des3.mode;
	rctx->cmd.u.des3.action = (encrypt)
				  ? CCP_DES3_ACTION_ENCRYPT
				  : CCP_DES3_ACTION_DECRYPT;
	rctx->cmd.u.des3.key = &ctx->u.des3.key_sg;
	rctx->cmd.u.des3.key_len = ctx->u.des3.key_len;
	rctx->cmd.u.des3.iv = iv_sg;
	rctx->cmd.u.des3.iv_len = iv_len;
	rctx->cmd.u.des3.src = req->src;
	rctx->cmd.u.des3.src_len = req->nbytes;
	rctx->cmd.u.des3.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	return ret;
}