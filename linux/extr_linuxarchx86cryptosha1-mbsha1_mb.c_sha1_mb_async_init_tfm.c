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
struct sha1_mb_ctx {struct mcryptd_ahash* mcryptd_tfm; } ;
struct mcryptd_hash_ctx {int /*<<< orphan*/ * alg_state; } ;
struct mcryptd_ahash {int /*<<< orphan*/  base; } ;
struct crypto_tfm {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_INTERNAL ; 
 scalar_t__ IS_ERR (struct mcryptd_ahash*) ; 
 int PTR_ERR (struct mcryptd_ahash*) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 struct mcryptd_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_ahash_reqsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sha1_mb_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct mcryptd_ahash* mcryptd_alloc_ahash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_mb_alg_state ; 

__attribute__((used)) static int sha1_mb_async_init_tfm(struct crypto_tfm *tfm)
{
	struct mcryptd_ahash *mcryptd_tfm;
	struct sha1_mb_ctx *ctx = crypto_tfm_ctx(tfm);
	struct mcryptd_hash_ctx *mctx;

	mcryptd_tfm = mcryptd_alloc_ahash("__intel_sha1-mb",
						CRYPTO_ALG_INTERNAL,
						CRYPTO_ALG_INTERNAL);
	if (IS_ERR(mcryptd_tfm))
		return PTR_ERR(mcryptd_tfm);
	mctx = crypto_ahash_ctx(&mcryptd_tfm->base);
	mctx->alg_state = &sha1_mb_alg_state;
	ctx->mcryptd_tfm = mcryptd_tfm;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				sizeof(struct ahash_request) +
				crypto_ahash_reqsize(&mcryptd_tfm->base));

	return 0;
}