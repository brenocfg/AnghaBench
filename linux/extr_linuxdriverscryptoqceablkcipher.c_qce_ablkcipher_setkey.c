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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qce_cipher_ctx {unsigned int enc_keylen; int /*<<< orphan*/  fallback; int /*<<< orphan*/  enc_key; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_2__ {unsigned long alg_flags; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 129 
#define  AES_KEYSIZE_256 128 
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 int EINVAL ; 
 scalar_t__ IS_AES (unsigned long) ; 
 scalar_t__ IS_DES (unsigned long) ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int crypto_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct qce_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 TYPE_1__* to_cipher_tmpl (struct crypto_tfm*) ; 

__attribute__((used)) static int qce_ablkcipher_setkey(struct crypto_ablkcipher *ablk, const u8 *key,
				 unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(ablk);
	struct qce_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	unsigned long flags = to_cipher_tmpl(tfm)->alg_flags;
	int ret;

	if (!key || !keylen)
		return -EINVAL;

	if (IS_AES(flags)) {
		switch (keylen) {
		case AES_KEYSIZE_128:
		case AES_KEYSIZE_256:
			break;
		default:
			goto fallback;
		}
	} else if (IS_DES(flags)) {
		u32 tmp[DES_EXPKEY_WORDS];

		ret = des_ekey(tmp, key);
		if (!ret && crypto_ablkcipher_get_flags(ablk) &
		    CRYPTO_TFM_REQ_WEAK_KEY)
			goto weakkey;
	}

	ctx->enc_keylen = keylen;
	memcpy(ctx->enc_key, key, keylen);
	return 0;
fallback:
	ret = crypto_skcipher_setkey(ctx->fallback, key, keylen);
	if (!ret)
		ctx->enc_keylen = keylen;
	return ret;
weakkey:
	crypto_ablkcipher_set_flags(ablk, CRYPTO_TFM_RES_WEAK_KEY);
	return -EINVAL;
}