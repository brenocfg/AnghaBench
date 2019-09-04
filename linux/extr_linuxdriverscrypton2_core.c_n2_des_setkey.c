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
struct TYPE_2__ {int /*<<< orphan*/  des; } ;
struct n2_cipher_context {unsigned int key_len; TYPE_1__ key; int /*<<< orphan*/  enc_type; } ;
struct n2_cipher_alg {int /*<<< orphan*/  enc_type; } ;
struct crypto_tfm {int crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct n2_cipher_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct n2_cipher_alg* n2_cipher_alg (struct crypto_tfm*) ; 

__attribute__((used)) static int n2_des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			 unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct n2_cipher_context *ctx = crypto_tfm_ctx(tfm);
	struct n2_cipher_alg *n2alg = n2_cipher_alg(tfm);
	u32 tmp[DES_EXPKEY_WORDS];
	int err;

	ctx->enc_type = n2alg->enc_type;

	if (keylen != DES_KEY_SIZE) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	err = des_ekey(tmp, key);
	if (err == 0 && (tfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	ctx->key_len = keylen;
	memcpy(ctx->key.des, key, keylen);
	return 0;
}