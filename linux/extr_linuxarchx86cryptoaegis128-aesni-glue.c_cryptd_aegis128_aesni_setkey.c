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
struct crypto_aead {int dummy; } ;
struct cryptd_aead {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_aead** crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int cryptd_aegis128_aesni_setkey(struct crypto_aead *aead,
					const u8 *key, unsigned int keylen)
{
	struct cryptd_aead **ctx = crypto_aead_ctx(aead);
	struct cryptd_aead *cryptd_tfm = *ctx;

	return crypto_aead_setkey(&cryptd_tfm->base, key, keylen);
}