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
struct crypto_skcipher {int /*<<< orphan*/  keysize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_blkcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_keysize; } ;
struct crypto_alg {TYPE_1__ cra_blkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 int PTR_ERR (struct crypto_tfm*) ; 
 struct crypto_tfm* __crypto_alloc_tfm (struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_blkcipher* __crypto_blkcipher_cast (struct crypto_tfm*) ; 
 struct crypto_skcipher* __crypto_skcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_blkcipher_ivsize (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  crypto_exit_skcipher_ops_blkcipher ; 
 int /*<<< orphan*/  crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 struct crypto_blkcipher** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  skcipher_decrypt_blkcipher ; 
 int /*<<< orphan*/  skcipher_encrypt_blkcipher ; 
 int /*<<< orphan*/  skcipher_set_needkey (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  skcipher_setkey_blkcipher ; 

__attribute__((used)) static int crypto_init_skcipher_ops_blkcipher(struct crypto_tfm *tfm)
{
	struct crypto_alg *calg = tfm->__crt_alg;
	struct crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	struct crypto_blkcipher **ctx = crypto_tfm_ctx(tfm);
	struct crypto_blkcipher *blkcipher;
	struct crypto_tfm *btfm;

	if (!crypto_mod_get(calg))
		return -EAGAIN;

	btfm = __crypto_alloc_tfm(calg, CRYPTO_ALG_TYPE_BLKCIPHER,
					CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(btfm)) {
		crypto_mod_put(calg);
		return PTR_ERR(btfm);
	}

	blkcipher = __crypto_blkcipher_cast(btfm);
	*ctx = blkcipher;
	tfm->exit = crypto_exit_skcipher_ops_blkcipher;

	skcipher->setkey = skcipher_setkey_blkcipher;
	skcipher->encrypt = skcipher_encrypt_blkcipher;
	skcipher->decrypt = skcipher_decrypt_blkcipher;

	skcipher->ivsize = crypto_blkcipher_ivsize(blkcipher);
	skcipher->keysize = calg->cra_blkcipher.max_keysize;

	skcipher_set_needkey(skcipher);

	return 0;
}