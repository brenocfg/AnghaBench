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
typedef  int u64 ;
struct ghash_key {int a; int b; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int GHASH_BLOCK_SIZE ; 
 struct ghash_key* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 
 int get_unaligned_be64 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ghash_setkey(struct crypto_shash *tfm,
			const u8 *inkey, unsigned int keylen)
{
	struct ghash_key *key = crypto_shash_ctx(tfm);
	u64 a, b;

	if (keylen != GHASH_BLOCK_SIZE) {
		crypto_shash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* perform multiplication by 'x' in GF(2^128) */
	b = get_unaligned_be64(inkey);
	a = get_unaligned_be64(inkey + 8);

	key->a = (a << 1) | (b >> 63);
	key->b = (b << 1) | (a >> 63);

	if (b >> 63)
		key->b ^= 0xc200000000000000UL;

	return 0;
}