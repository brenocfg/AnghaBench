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
struct TYPE_2__ {int /*<<< orphan*/  crt_flags; } ;
struct crypto_skcipher {TYPE_1__ base; } ;
struct camellia_xts_ctx {int /*<<< orphan*/  tweak_ctx; int /*<<< orphan*/  crypt_ctx; } ;

/* Variables and functions */
 int __camellia_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 struct camellia_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int xts_verify_key (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 

int xts_camellia_setkey(struct crypto_skcipher *tfm, const u8 *key,
			unsigned int keylen)
{
	struct camellia_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 *flags = &tfm->base.crt_flags;
	int err;

	err = xts_verify_key(tfm, key, keylen);
	if (err)
		return err;

	/* first half of xts-key is for crypt */
	err = __camellia_setkey(&ctx->crypt_ctx, key, keylen / 2, flags);
	if (err)
		return err;

	/* second half of xts-key is for tweak */
	return __camellia_setkey(&ctx->tweak_ctx, key + keylen / 2, keylen / 2,
				flags);
}