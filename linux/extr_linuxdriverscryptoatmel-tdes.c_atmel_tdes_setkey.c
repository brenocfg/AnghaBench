#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ablkcipher {int dummy; } ;
struct atmel_tdes_ctx {unsigned int keylen; int /*<<< orphan*/  key; TYPE_2__* dd; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_cfb_3keys; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int DES_KEY_SIZE ; 
 int EINVAL ; 
 struct atmel_tdes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 char* crypto_tfm_alg_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static int atmel_tdes_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct atmel_tdes_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	const char *alg_name;

	alg_name = crypto_tfm_alg_name(crypto_ablkcipher_tfm(tfm));

	/*
	 * HW bug in cfb 3-keys mode.
	 */
	if (!ctx->dd->caps.has_cfb_3keys && strstr(alg_name, "cfb")
			&& (keylen != 2*DES_KEY_SIZE)) {
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	} else if ((keylen != 2*DES_KEY_SIZE) && (keylen != 3*DES_KEY_SIZE)) {
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	memcpy(ctx->key, key, keylen);
	ctx->keylen = keylen;

	return 0;
}