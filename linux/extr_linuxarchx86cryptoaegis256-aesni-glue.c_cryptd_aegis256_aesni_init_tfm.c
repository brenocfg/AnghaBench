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
 int /*<<< orphan*/  CRYPTO_ALG_INTERNAL ; 
 scalar_t__ IS_ERR (struct cryptd_aead*) ; 
 int PTR_ERR (struct cryptd_aead*) ; 
 struct cryptd_aead* cryptd_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cryptd_aead** crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_reqsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptd_aegis256_aesni_init_tfm(struct crypto_aead *aead)
{
	struct cryptd_aead *cryptd_tfm;
	struct cryptd_aead **ctx = crypto_aead_ctx(aead);

	cryptd_tfm = cryptd_alloc_aead("__aegis256-aesni", CRYPTO_ALG_INTERNAL,
				       CRYPTO_ALG_INTERNAL);
	if (IS_ERR(cryptd_tfm))
		return PTR_ERR(cryptd_tfm);

	*ctx = cryptd_tfm;
	crypto_aead_set_reqsize(aead, crypto_aead_reqsize(&cryptd_tfm->base));
	return 0;
}