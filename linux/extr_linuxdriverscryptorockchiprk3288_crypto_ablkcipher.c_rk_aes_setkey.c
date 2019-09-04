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
struct rk_cipher_ctx {unsigned int keylen; TYPE_1__* dev; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ RK_CRYPTO_AES_KEY_0 ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct rk_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int rk_aes_setkey(struct crypto_ablkcipher *cipher,
			 const u8 *key, unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct rk_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	if (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	ctx->keylen = keylen;
	memcpy_toio(ctx->dev->reg + RK_CRYPTO_AES_KEY_0, key, keylen);
	return 0;
}