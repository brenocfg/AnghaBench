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
struct sha256_mb_ctx {struct mcryptd_ahash* mcryptd_tfm; } ;
struct ahash_request {int dummy; } ;
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  complete; struct ahash_request areq; } ;
struct crypto_ahash {int dummy; } ;
struct mcryptd_ahash {struct crypto_ahash base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 void* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,struct crypto_ahash*) ; 
 struct sha256_mb_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_import (struct ahash_request*,void const*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 struct crypto_ahash* mcryptd_ahash_child (struct mcryptd_ahash*) ; 
 int /*<<< orphan*/  memcpy (struct ahash_request*,struct ahash_request*,int) ; 

__attribute__((used)) static int sha256_mb_async_import(struct ahash_request *req, const void *in)
{
	struct ahash_request *mcryptd_req = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct sha256_mb_ctx *ctx = crypto_ahash_ctx(tfm);
	struct mcryptd_ahash *mcryptd_tfm = ctx->mcryptd_tfm;
	struct crypto_ahash *child = mcryptd_ahash_child(mcryptd_tfm);
	struct mcryptd_hash_request_ctx *rctx;
	struct ahash_request *areq;

	memcpy(mcryptd_req, req, sizeof(*req));
	ahash_request_set_tfm(mcryptd_req, &mcryptd_tfm->base);
	rctx = ahash_request_ctx(mcryptd_req);
	areq = &rctx->areq;

	ahash_request_set_tfm(areq, child);
	ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_SLEEP,
					rctx->complete, req);

	return crypto_ahash_import(mcryptd_req, in);
}