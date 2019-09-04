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
struct spacc_ablk_ctx {unsigned int key_len; int /*<<< orphan*/  key; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 unsigned int DES3_EDE_KEY_SIZE ; 
 int DES_EXPKEY_WORDS ; 
 int EINVAL ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct spacc_ablk_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int spacc_des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			    unsigned int len)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct spacc_ablk_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 tmp[DES_EXPKEY_WORDS];

	if (len > DES3_EDE_KEY_SIZE) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	if (unlikely(!des_ekey(tmp, key)) &&
	    (crypto_ablkcipher_get_flags(cipher) & CRYPTO_TFM_REQ_WEAK_KEY)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	memcpy(ctx->key, key, len);
	ctx->key_len = len;

	return 0;
}