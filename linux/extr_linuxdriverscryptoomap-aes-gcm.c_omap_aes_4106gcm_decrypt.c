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
struct omap_aes_reqctx {scalar_t__ iv; } ;
struct omap_aes_ctx {int /*<<< orphan*/  nonce; } ;
struct aead_request {int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int FLAGS_GCM ; 
 int FLAGS_RFC4106_GCM ; 
 struct omap_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 struct omap_aes_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int omap_aes_gcm_crypt (struct aead_request*,int) ; 

int omap_aes_4106gcm_decrypt(struct aead_request *req)
{
	struct omap_aes_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct omap_aes_reqctx *rctx = aead_request_ctx(req);

	memcpy(rctx->iv, ctx->nonce, 4);
	memcpy(rctx->iv + 4, req->iv, 8);
	return omap_aes_gcm_crypt(req, FLAGS_GCM | FLAGS_RFC4106_GCM);
}