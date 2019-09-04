#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct img_hash_request_ctx {TYPE_3__ fallback_req; } ;
struct img_hash_ctx {int /*<<< orphan*/  fallback; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct ahash_request {TYPE_2__ base; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 struct img_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct img_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_import (TYPE_3__*,void const*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 

__attribute__((used)) static int img_hash_import(struct ahash_request *req, const void *in)
{
	struct img_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct img_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	rctx->fallback_req.base.flags = req->base.flags
		& CRYPTO_TFM_REQ_MAY_SLEEP;

	return crypto_ahash_import(&rctx->fallback_req, in);
}