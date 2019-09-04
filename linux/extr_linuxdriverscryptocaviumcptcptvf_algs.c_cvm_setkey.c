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
struct cvm_enc_ctx {int /*<<< orphan*/  enc_key; int /*<<< orphan*/  cipher_type; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct cvm_enc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  cvm_validate_keylen (struct cvm_enc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cvm_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		      u32 keylen, u8 cipher_type)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct cvm_enc_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->cipher_type = cipher_type;
	if (!cvm_validate_keylen(ctx, keylen)) {
		memcpy(ctx->enc_key, key, keylen);
		return 0;
	} else {
		crypto_ablkcipher_set_flags(cipher,
					    CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
}