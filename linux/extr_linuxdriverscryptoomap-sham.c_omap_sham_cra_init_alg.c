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
struct omap_sham_reqctx {int dummy; } ;
struct omap_sham_hmac_ctx {void* shash; } ;
struct omap_sham_ctx {void* fallback; int /*<<< orphan*/  flags; struct omap_sham_hmac_ctx* base; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BUFLEN ; 
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 int /*<<< orphan*/  FLAGS_HMAC ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,scalar_t__) ; 
 void* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (void*) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct omap_sham_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int omap_sham_cra_init_alg(struct crypto_tfm *tfm, const char *alg_base)
{
	struct omap_sham_ctx *tctx = crypto_tfm_ctx(tfm);
	const char *alg_name = crypto_tfm_alg_name(tfm);

	/* Allocate a fallback and abort if it failed. */
	tctx->fallback = crypto_alloc_shash(alg_name, 0,
					    CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(tctx->fallback)) {
		pr_err("omap-sham: fallback driver '%s' "
				"could not be loaded.\n", alg_name);
		return PTR_ERR(tctx->fallback);
	}

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct omap_sham_reqctx) + BUFLEN);

	if (alg_base) {
		struct omap_sham_hmac_ctx *bctx = tctx->base;
		tctx->flags |= BIT(FLAGS_HMAC);
		bctx->shash = crypto_alloc_shash(alg_base, 0,
						CRYPTO_ALG_NEED_FALLBACK);
		if (IS_ERR(bctx->shash)) {
			pr_err("omap-sham: base driver '%s' "
					"could not be loaded.\n", alg_base);
			crypto_free_shash(tctx->fallback);
			return PTR_ERR(bctx->shash);
		}

	}

	return 0;
}