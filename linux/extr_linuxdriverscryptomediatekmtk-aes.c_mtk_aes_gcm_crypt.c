#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct mtk_aes_reqctx {int mode; } ;
struct mtk_aes_gcm_ctx {int /*<<< orphan*/  textlen; } ;
struct mtk_aes_base_ctx {int /*<<< orphan*/  cryp; } ;
struct aead_request {int /*<<< orphan*/  base; int /*<<< orphan*/  assoclen; } ;

/* Variables and functions */
 int AES_FLAGS_ENCRYPT ; 
 int AES_FLAGS_GCM ; 
 int EINVAL ; 
 struct mtk_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 struct mtk_aes_base_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 struct mtk_aes_gcm_ctx* mtk_aes_gcm_ctx_cast (struct mtk_aes_base_ctx*) ; 
 int mtk_aes_handle_queue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_aes_gcm_crypt(struct aead_request *req, u64 mode)
{
	struct mtk_aes_base_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct mtk_aes_gcm_ctx *gctx = mtk_aes_gcm_ctx_cast(ctx);
	struct mtk_aes_reqctx *rctx = aead_request_ctx(req);

	/* Empty messages are not supported yet */
	if (!gctx->textlen && !req->assoclen)
		return -EINVAL;

	rctx->mode = AES_FLAGS_GCM | mode;

	return mtk_aes_handle_queue(ctx->cryp, !!(mode & AES_FLAGS_ENCRYPT),
				    &req->base);
}