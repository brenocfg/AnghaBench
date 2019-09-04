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
struct TYPE_2__ {struct crypto_shash* fallback_tfm; } ;
struct n2_hmac_ctx {TYPE_1__ base; struct crypto_shash* child_shash; } ;
struct n2_hmac_alg {char const* child_alg; } ;
struct n2_hash_req_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_shash {int dummy; } ;
typedef  struct crypto_shash crypto_ahash ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 struct n2_hmac_ctx* crypto_ahash_ctx (struct crypto_shash*) ; 
 scalar_t__ crypto_ahash_reqsize (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (struct crypto_shash*,scalar_t__) ; 
 struct crypto_shash* crypto_alloc_ahash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_shash*) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct n2_hmac_alg* n2_hmac_alg (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 

__attribute__((used)) static int n2_hmac_cra_init(struct crypto_tfm *tfm)
{
	const char *fallback_driver_name = crypto_tfm_alg_name(tfm);
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct n2_hmac_ctx *ctx = crypto_ahash_ctx(ahash);
	struct n2_hmac_alg *n2alg = n2_hmac_alg(tfm);
	struct crypto_ahash *fallback_tfm;
	struct crypto_shash *child_shash;
	int err;

	fallback_tfm = crypto_alloc_ahash(fallback_driver_name, 0,
					  CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(fallback_tfm)) {
		pr_warning("Fallback driver '%s' could not be loaded!\n",
			   fallback_driver_name);
		err = PTR_ERR(fallback_tfm);
		goto out;
	}

	child_shash = crypto_alloc_shash(n2alg->child_alg, 0, 0);
	if (IS_ERR(child_shash)) {
		pr_warning("Child shash '%s' could not be loaded!\n",
			   n2alg->child_alg);
		err = PTR_ERR(child_shash);
		goto out_free_fallback;
	}

	crypto_ahash_set_reqsize(ahash, (sizeof(struct n2_hash_req_ctx) +
					 crypto_ahash_reqsize(fallback_tfm)));

	ctx->child_shash = child_shash;
	ctx->base.fallback_tfm = fallback_tfm;
	return 0;

out_free_fallback:
	crypto_free_ahash(fallback_tfm);

out:
	return err;
}