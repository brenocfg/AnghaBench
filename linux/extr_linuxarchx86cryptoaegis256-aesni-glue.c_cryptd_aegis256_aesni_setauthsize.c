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
struct crypto_aead {int dummy; } ;
struct cryptd_aead {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_aead** crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int cryptd_aegis256_aesni_setauthsize(struct crypto_aead *aead,
					     unsigned int authsize)
{
	struct cryptd_aead **ctx = crypto_aead_ctx(aead);
	struct cryptd_aead *cryptd_tfm = *ctx;

	return crypto_aead_setauthsize(&cryptd_tfm->base, authsize);
}