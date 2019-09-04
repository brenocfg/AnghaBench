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
struct mtk_sha_reqctx {int dummy; } ;
struct mtk_sha_hmac_ctx {int /*<<< orphan*/  shash; } ;
struct mtk_sha_ctx {int /*<<< orphan*/  flags; struct mtk_sha_hmac_ctx* base; } ;
struct mtk_cryp {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA_FLAGS_HMAC ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_sha_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct mtk_cryp* mtk_sha_find_dev (struct mtk_sha_ctx*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int mtk_sha_cra_init_alg(struct crypto_tfm *tfm,
				const char *alg_base)
{
	struct mtk_sha_ctx *tctx = crypto_tfm_ctx(tfm);
	struct mtk_cryp *cryp = NULL;

	cryp = mtk_sha_find_dev(tctx);
	if (!cryp)
		return -ENODEV;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct mtk_sha_reqctx));

	if (alg_base) {
		struct mtk_sha_hmac_ctx *bctx = tctx->base;

		tctx->flags |= SHA_FLAGS_HMAC;
		bctx->shash = crypto_alloc_shash(alg_base, 0,
					CRYPTO_ALG_NEED_FALLBACK);
		if (IS_ERR(bctx->shash)) {
			pr_err("base driver %s could not be loaded.\n",
			       alg_base);

			return PTR_ERR(bctx->shash);
		}
	}
	return 0;
}