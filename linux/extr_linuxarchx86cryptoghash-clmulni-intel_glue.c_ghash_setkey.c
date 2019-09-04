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
typedef  int u64 ;
struct TYPE_3__ {int a; int b; } ;
struct ghash_ctx {TYPE_1__ shash; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_2__ be128 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int GHASH_BLOCK_SIZE ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ghash_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ghash_setkey(struct crypto_shash *tfm,
			const u8 *key, unsigned int keylen)
{
	struct ghash_ctx *ctx = crypto_shash_ctx(tfm);
	be128 *x = (be128 *)key;
	u64 a, b;

	if (keylen != GHASH_BLOCK_SIZE) {
		crypto_shash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* perform multiplication by 'x' in GF(2^128) */
	a = be64_to_cpu(x->a);
	b = be64_to_cpu(x->b);

	ctx->shash.a = (b << 1) | (a >> 63);
	ctx->shash.b = (a << 1) | (b >> 63);

	if (a >> 63)
		ctx->shash.b ^= ((u64)0xc2) << 56;

	return 0;
}