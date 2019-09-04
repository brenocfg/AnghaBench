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
struct crypto_tfm {int crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;
struct atmel_tdes_ctx {unsigned int keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct atmel_tdes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int atmel_des_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			   unsigned int keylen)
{
	u32 tmp[DES_EXPKEY_WORDS];
	int err;
	struct crypto_tfm *ctfm = crypto_ablkcipher_tfm(tfm);

	struct atmel_tdes_ctx *ctx = crypto_ablkcipher_ctx(tfm);

	if (keylen != DES_KEY_SIZE) {
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	err = des_ekey(tmp, key);
	if (err == 0 && (ctfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		ctfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	memcpy(ctx->key, key, keylen);
	ctx->keylen = keylen;

	return 0;
}