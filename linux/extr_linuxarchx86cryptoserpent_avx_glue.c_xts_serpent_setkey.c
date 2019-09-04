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
struct serpent_xts_ctx {int /*<<< orphan*/  tweak_ctx; int /*<<< orphan*/  crypt_ctx; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int __serpent_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct serpent_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int xts_verify_key (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 

int xts_serpent_setkey(struct crypto_skcipher *tfm, const u8 *key,
		       unsigned int keylen)
{
	struct serpent_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	int err;

	err = xts_verify_key(tfm, key, keylen);
	if (err)
		return err;

	/* first half of xts-key is for crypt */
	err = __serpent_setkey(&ctx->crypt_ctx, key, keylen / 2);
	if (err)
		return err;

	/* second half of xts-key is for tweak */
	return __serpent_setkey(&ctx->tweak_ctx, key + keylen / 2, keylen / 2);
}