#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct n2_hmac_ctx {scalar_t__ hash_key_len; int /*<<< orphan*/  hash_key; } ;
struct TYPE_8__ {int digest_size; int /*<<< orphan*/  hw_op_hashsz; int /*<<< orphan*/  hmac_type; int /*<<< orphan*/  hash_init; } ;
struct n2_hmac_alg {TYPE_3__ derived; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_9__ {scalar_t__ nbytes; int /*<<< orphan*/  result; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct n2_hash_req_ctx {int /*<<< orphan*/  u; TYPE_4__ fallback_req; } ;
struct n2_hash_ctx {int /*<<< orphan*/  fallback_tfm; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  tfm; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  result; int /*<<< orphan*/  src; TYPE_2__ base; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 scalar_t__ N2_HASH_KEY_MAX ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct n2_hash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digest (TYPE_4__*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int n2_do_async_digest (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct n2_hmac_alg* n2_hmac_alg (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int n2_hmac_async_digest(struct ahash_request *req)
{
	struct n2_hmac_alg *n2alg = n2_hmac_alg(req->base.tfm);
	struct n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct n2_hmac_ctx *ctx = crypto_ahash_ctx(tfm);
	int ds;

	ds = n2alg->derived.digest_size;
	if (unlikely(req->nbytes == 0) ||
	    unlikely(ctx->hash_key_len > N2_HASH_KEY_MAX)) {
		struct n2_hash_req_ctx *rctx = ahash_request_ctx(req);
		struct n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

		ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
		rctx->fallback_req.base.flags =
			req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
		rctx->fallback_req.nbytes = req->nbytes;
		rctx->fallback_req.src = req->src;
		rctx->fallback_req.result = req->result;

		return crypto_ahash_digest(&rctx->fallback_req);
	}
	memcpy(&rctx->u, n2alg->derived.hash_init,
	       n2alg->derived.hw_op_hashsz);

	return n2_do_async_digest(req, n2alg->derived.hmac_type,
				  n2alg->derived.hw_op_hashsz, ds,
				  &rctx->u,
				  __pa(&ctx->hash_key),
				  ctx->hash_key_len);
}