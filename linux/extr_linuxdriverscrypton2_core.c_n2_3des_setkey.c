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
struct TYPE_2__ {int /*<<< orphan*/  des3; } ;
struct n2_cipher_context {unsigned int key_len; TYPE_1__ key; int /*<<< orphan*/  enc_type; } ;
struct n2_cipher_alg {int /*<<< orphan*/  enc_type; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int DES_KEY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct n2_cipher_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct n2_cipher_alg* n2_cipher_alg (struct crypto_tfm*) ; 

__attribute__((used)) static int n2_3des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			  unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct n2_cipher_context *ctx = crypto_tfm_ctx(tfm);
	struct n2_cipher_alg *n2alg = n2_cipher_alg(tfm);

	ctx->enc_type = n2alg->enc_type;

	if (keylen != (3 * DES_KEY_SIZE)) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	ctx->key_len = keylen;
	memcpy(ctx->key.des3, key, keylen);
	return 0;
}