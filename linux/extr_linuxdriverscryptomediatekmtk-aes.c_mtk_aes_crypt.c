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
struct mtk_aes_base_ctx {int /*<<< orphan*/  cryp; } ;
struct ablkcipher_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int AES_FLAGS_ENCRYPT ; 
 struct mtk_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct mtk_aes_base_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int mtk_aes_handle_queue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_aes_crypt(struct ablkcipher_request *req, u64 mode)
{
	struct mtk_aes_base_ctx *ctx;
	struct mtk_aes_reqctx *rctx;

	ctx = crypto_ablkcipher_ctx(crypto_ablkcipher_reqtfm(req));
	rctx = ablkcipher_request_ctx(req);
	rctx->mode = mode;

	return mtk_aes_handle_queue(ctx->cryp, !(mode & AES_FLAGS_ENCRYPT),
				    &req->base);
}