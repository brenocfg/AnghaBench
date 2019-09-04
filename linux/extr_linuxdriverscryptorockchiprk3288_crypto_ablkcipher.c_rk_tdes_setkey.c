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
struct rk_cipher_ctx {unsigned int keylen; TYPE_1__* dev; } ;
struct crypto_tfm {int crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 unsigned int DES3_EDE_KEY_SIZE ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 scalar_t__ RK_CRYPTO_TDES_KEY1_0 ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct rk_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int rk_tdes_setkey(struct crypto_ablkcipher *cipher,
			  const u8 *key, unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct rk_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 tmp[DES_EXPKEY_WORDS];

	if (keylen != DES_KEY_SIZE && keylen != DES3_EDE_KEY_SIZE) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	if (keylen == DES_KEY_SIZE) {
		if (!des_ekey(tmp, key) &&
		    (tfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
			tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
			return -EINVAL;
		}
	}

	ctx->keylen = keylen;
	memcpy_toio(ctx->dev->reg + RK_CRYPTO_TDES_KEY1_0, key, keylen);
	return 0;
}