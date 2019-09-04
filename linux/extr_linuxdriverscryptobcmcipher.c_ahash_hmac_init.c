#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iproc_reqctx_s {int is_sw_hmac; unsigned int hash_carry_len; unsigned int total_todo; int /*<<< orphan*/  hash_carry; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct iproc_ctx_s {int /*<<< orphan*/  ipad; TYPE_1__ auth; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_MODE_HASH ; 
 int /*<<< orphan*/  ahash_init (struct ahash_request*) ; 
 struct iproc_reqctx_s* ahash_request_ctx (struct ahash_request*) ; 
 struct iproc_ctx_s* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_log (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spu_no_incr_hash (struct iproc_ctx_s*) ; 

__attribute__((used)) static int ahash_hmac_init(struct ahash_request *req)
{
	struct iproc_reqctx_s *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	unsigned int blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	flow_log("ahash_hmac_init()\n");

	/* init the context as a hash */
	ahash_init(req);

	if (!spu_no_incr_hash(ctx)) {
		/* SPU-M can do incr hashing but needs sw for outer HMAC */
		rctx->is_sw_hmac = true;
		ctx->auth.mode = HASH_MODE_HASH;
		/* start with a prepended ipad */
		memcpy(rctx->hash_carry, ctx->ipad, blocksize);
		rctx->hash_carry_len = blocksize;
		rctx->total_todo += blocksize;
	}

	return 0;
}