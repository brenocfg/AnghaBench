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
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr_dma; } ;
struct safexcel_cipher_ctx {unsigned int key_len; int /*<<< orphan*/  key; TYPE_1__ base; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 unsigned int DES3_EDE_KEY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int safexcel_des3_ede_setkey(struct crypto_skcipher *ctfm,
				   const u8 *key, unsigned int len)
{
	struct crypto_tfm *tfm = crypto_skcipher_tfm(ctfm);
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	if (len != DES3_EDE_KEY_SIZE) {
		crypto_skcipher_set_flags(ctfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* if context exits and key changed, need to invalidate it */
	if (ctx->base.ctxr_dma) {
		if (memcmp(ctx->key, key, len))
			ctx->base.needs_inv = true;
	}

	memcpy(ctx->key, key, len);

	ctx->key_len = len;

	return 0;
}