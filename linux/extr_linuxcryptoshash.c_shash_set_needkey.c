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
struct TYPE_2__ {int cra_flags; } ;
struct shash_alg {TYPE_1__ base; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_OPTIONAL_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_NEED_KEY ; 
 scalar_t__ crypto_shash_alg_has_setkey (struct shash_alg*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shash_set_needkey(struct crypto_shash *tfm, struct shash_alg *alg)
{
	if (crypto_shash_alg_has_setkey(alg) &&
	    !(alg->base.cra_flags & CRYPTO_ALG_OPTIONAL_KEY))
		crypto_shash_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
}