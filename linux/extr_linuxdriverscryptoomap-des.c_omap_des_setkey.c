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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct omap_des_ctx {unsigned int keylen; int /*<<< orphan*/  key; } ;
struct crypto_tfm {int crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct omap_des_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static int omap_des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			   unsigned int keylen)
{
	struct omap_des_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);

	if (keylen != DES_KEY_SIZE && keylen != (3*DES_KEY_SIZE))
		return -EINVAL;

	pr_debug("enter, keylen: %d\n", keylen);

	/* Do we need to test against weak key? */
	if (tfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY) {
		u32 tmp[DES_EXPKEY_WORDS];
		int ret = des_ekey(tmp, key);

		if (!ret) {
			tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
			return -EINVAL;
		}
	}

	memcpy(ctx->key, key, keylen);
	ctx->keylen = keylen;

	return 0;
}