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
struct mv_cesa_des_ctx {int /*<<< orphan*/  key; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 unsigned int DES3_EDE_KEY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct mv_cesa_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int mv_cesa_des3_ede_setkey(struct crypto_skcipher *cipher,
				   const u8 *key, unsigned int len)
{
	struct crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	struct mv_cesa_des_ctx *ctx = crypto_tfm_ctx(tfm);

	if (len != DES3_EDE_KEY_SIZE) {
		crypto_skcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	memcpy(ctx->key, key, DES3_EDE_KEY_SIZE);

	return 0;
}