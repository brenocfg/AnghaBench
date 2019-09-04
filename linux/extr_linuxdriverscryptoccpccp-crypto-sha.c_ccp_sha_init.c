#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_ahash {int dummy; } ;
struct ccp_sha_req_ctx {int first; unsigned int buf_count; int /*<<< orphan*/  buf; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipad; scalar_t__ key_len; } ;
struct TYPE_4__ {TYPE_1__ sha; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct ccp_crypto_ahash_alg {int /*<<< orphan*/  type; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ccp_sha_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct ccp_crypto_ahash_alg* ccp_crypto_ahash_alg (int /*<<< orphan*/ ) ; 
 struct ccp_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ccp_sha_req_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_sha_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ccp_ctx *ctx = crypto_ahash_ctx(tfm);
	struct ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	struct ccp_crypto_ahash_alg *alg =
		ccp_crypto_ahash_alg(crypto_ahash_tfm(tfm));
	unsigned int block_size =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	memset(rctx, 0, sizeof(*rctx));

	rctx->type = alg->type;
	rctx->first = 1;

	if (ctx->u.sha.key_len) {
		/* Buffer the HMAC key for first update */
		memcpy(rctx->buf, ctx->u.sha.ipad, block_size);
		rctx->buf_count = block_size;
	}

	return 0;
}