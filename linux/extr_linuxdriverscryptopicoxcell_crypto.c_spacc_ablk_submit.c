#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spacc_req {int ctx_id; int src_addr; int dst_addr; scalar_t__ is_encrypt; TYPE_3__* req; } ;
struct spacc_engine {scalar_t__ regs; int /*<<< orphan*/  packet_timeout; } ;
struct spacc_alg {int ctrl_default; } ;
struct TYPE_5__ {struct spacc_engine* engine; } ;
struct spacc_ablk_ctx {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; TYPE_2__ generic; } ;
struct crypto_tfm {struct crypto_alg* __crt_alg; } ;
struct TYPE_4__ {int /*<<< orphan*/  ivsize; } ;
struct crypto_alg {TYPE_1__ cra_ablkcipher; } ;
struct ablkcipher_request {int nbytes; int /*<<< orphan*/  info; } ;
struct TYPE_6__ {struct crypto_tfm* tfm; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ PACKET_TIMEOUT ; 
 scalar_t__ SPA_AAD_LEN_REG_OFFSET ; 
 scalar_t__ SPA_AUX_INFO_REG_OFFSET ; 
 int SPA_CTRL_CTX_IDX ; 
 int SPA_CTRL_ENCRYPT_IDX ; 
 int SPA_CTRL_KEY_EXP ; 
 scalar_t__ SPA_CTRL_REG_OFFSET ; 
 scalar_t__ SPA_DST_PTR_REG_OFFSET ; 
 scalar_t__ SPA_ICV_OFFSET_REG_OFFSET ; 
 scalar_t__ SPA_OFFSET_REG_OFFSET ; 
 scalar_t__ SPA_PROC_LEN_REG_OFFSET ; 
 scalar_t__ SPA_SRC_PTR_REG_OFFSET ; 
 struct ablkcipher_request* ablkcipher_request_cast (TYPE_3__*) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int spacc_load_ctx (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spacc_alg* to_spacc_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spacc_ablk_submit(struct spacc_req *req)
{
	struct crypto_tfm *tfm = req->req->tfm;
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(tfm);
	struct ablkcipher_request *ablk_req = ablkcipher_request_cast(req->req);
	struct crypto_alg *alg = req->req->tfm->__crt_alg;
	struct spacc_alg *spacc_alg = to_spacc_alg(alg);
	struct spacc_engine *engine = ctx->generic.engine;
	u32 ctrl;

	req->ctx_id = spacc_load_ctx(&ctx->generic, ctx->key,
		ctx->key_len, ablk_req->info, alg->cra_ablkcipher.ivsize,
		NULL, 0);

	writel(req->src_addr, engine->regs + SPA_SRC_PTR_REG_OFFSET);
	writel(req->dst_addr, engine->regs + SPA_DST_PTR_REG_OFFSET);
	writel(0, engine->regs + SPA_OFFSET_REG_OFFSET);

	writel(ablk_req->nbytes, engine->regs + SPA_PROC_LEN_REG_OFFSET);
	writel(0, engine->regs + SPA_ICV_OFFSET_REG_OFFSET);
	writel(0, engine->regs + SPA_AUX_INFO_REG_OFFSET);
	writel(0, engine->regs + SPA_AAD_LEN_REG_OFFSET);

	ctrl = spacc_alg->ctrl_default | (req->ctx_id << SPA_CTRL_CTX_IDX) |
		(req->is_encrypt ? (1 << SPA_CTRL_ENCRYPT_IDX) :
		 (1 << SPA_CTRL_KEY_EXP));

	mod_timer(&engine->packet_timeout, jiffies + PACKET_TIMEOUT);

	writel(ctrl, engine->regs + SPA_CTRL_REG_OFFSET);

	return -EINPROGRESS;
}