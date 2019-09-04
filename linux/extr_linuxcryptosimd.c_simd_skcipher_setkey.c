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
struct simd_skcipher_ctx {TYPE_1__* cryptd_tfm; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {struct crypto_skcipher base; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int) ; 
 struct simd_skcipher_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int simd_skcipher_setkey(struct crypto_skcipher *tfm, const u8 *key,
				unsigned int key_len)
{
	struct simd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *child = &ctx->cryptd_tfm->base;
	int err;

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(tfm) &
					 CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(child, key, key_len);
	crypto_skcipher_set_flags(tfm, crypto_skcipher_get_flags(child) &
				       CRYPTO_TFM_RES_MASK);
	return err;
}