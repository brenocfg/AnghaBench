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
struct crypto_tfm {int /*<<< orphan*/  exit; struct crypto_alg* __crt_alg; } ;
struct crypto_skcipher {int /*<<< orphan*/  keysize; scalar_t__ reqsize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_keysize; } ;
struct crypto_alg {TYPE_1__ cra_ablkcipher; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 int PTR_ERR (struct crypto_tfm*) ; 
 struct crypto_ablkcipher* __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 struct crypto_tfm* __crypto_alloc_tfm (struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* __crypto_skcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_reqsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_exit_skcipher_ops_ablkcipher ; 
 int /*<<< orphan*/  crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 struct crypto_ablkcipher** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  skcipher_decrypt_ablkcipher ; 
 int /*<<< orphan*/  skcipher_encrypt_ablkcipher ; 
 int /*<<< orphan*/  skcipher_set_needkey (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  skcipher_setkey_ablkcipher ; 

__attribute__((used)) static int crypto_init_skcipher_ops_ablkcipher(struct crypto_tfm *tfm)
{
	struct crypto_alg *calg = tfm->__crt_alg;
	struct crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	struct crypto_ablkcipher **ctx = crypto_tfm_ctx(tfm);
	struct crypto_ablkcipher *ablkcipher;
	struct crypto_tfm *abtfm;

	if (!crypto_mod_get(calg))
		return -EAGAIN;

	abtfm = __crypto_alloc_tfm(calg, 0, 0);
	if (IS_ERR(abtfm)) {
		crypto_mod_put(calg);
		return PTR_ERR(abtfm);
	}

	ablkcipher = __crypto_ablkcipher_cast(abtfm);
	*ctx = ablkcipher;
	tfm->exit = crypto_exit_skcipher_ops_ablkcipher;

	skcipher->setkey = skcipher_setkey_ablkcipher;
	skcipher->encrypt = skcipher_encrypt_ablkcipher;
	skcipher->decrypt = skcipher_decrypt_ablkcipher;

	skcipher->ivsize = crypto_ablkcipher_ivsize(ablkcipher);
	skcipher->reqsize = crypto_ablkcipher_reqsize(ablkcipher) +
			    sizeof(struct ablkcipher_request);
	skcipher->keysize = calg->cra_ablkcipher.max_keysize;

	skcipher_set_needkey(skcipher);

	return 0;
}