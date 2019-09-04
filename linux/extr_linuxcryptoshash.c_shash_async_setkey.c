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
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 struct crypto_shash** crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int shash_async_setkey(struct crypto_ahash *tfm, const u8 *key,
			      unsigned int keylen)
{
	struct crypto_shash **ctx = crypto_ahash_ctx(tfm);

	return crypto_shash_setkey(*ctx, key, keylen);
}