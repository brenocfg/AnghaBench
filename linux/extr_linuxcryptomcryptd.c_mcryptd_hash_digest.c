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
struct ahash_request {int /*<<< orphan*/  base; int /*<<< orphan*/  result; } ;
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  out; struct ahash_request areq; } ;
struct mcryptd_hash_ctx {struct crypto_ahash* child; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct mcryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int),struct crypto_async_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,struct crypto_ahash*) ; 
 int crypto_ahash_finup (struct ahash_request*) ; 
 scalar_t__ crypto_ahash_init (struct ahash_request*) ; 
 struct mcryptd_hash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mcryptd_hash_digest(struct crypto_async_request *req_async, int err)
{
	struct mcryptd_hash_ctx *ctx = crypto_tfm_ctx(req_async->tfm);
	struct crypto_ahash *child = ctx->child;
	struct ahash_request *req = ahash_request_cast(req_async);
	struct mcryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct ahash_request *desc = &rctx->areq;

	if (unlikely(err == -EINPROGRESS))
		goto out;

	ahash_request_set_tfm(desc, child);
	ahash_request_set_callback(desc, CRYPTO_TFM_REQ_MAY_SLEEP,
						rctx->complete, req_async);

	rctx->out = req->result;
	err = crypto_ahash_init(desc) ?: crypto_ahash_finup(desc);

out:
	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();
}