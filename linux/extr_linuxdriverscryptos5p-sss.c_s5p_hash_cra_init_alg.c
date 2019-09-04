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
struct s5p_hash_reqctx {int dummy; } ;
struct s5p_hash_ctx {int /*<<< orphan*/  fallback; int /*<<< orphan*/  dd; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct s5p_hash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  s5p_dev ; 

__attribute__((used)) static int s5p_hash_cra_init_alg(struct crypto_tfm *tfm)
{
	struct s5p_hash_ctx *tctx = crypto_tfm_ctx(tfm);
	const char *alg_name = crypto_tfm_alg_name(tfm);

	tctx->dd = s5p_dev;
	/* Allocate a fallback and abort if it failed. */
	tctx->fallback = crypto_alloc_shash(alg_name, 0,
					    CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(tctx->fallback)) {
		pr_err("fallback alloc fails for '%s'\n", alg_name);
		return PTR_ERR(tctx->fallback);
	}

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct s5p_hash_reqctx) + BUFLEN);

	return 0;
}