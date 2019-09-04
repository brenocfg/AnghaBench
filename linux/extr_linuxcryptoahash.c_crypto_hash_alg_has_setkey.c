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
struct crypto_alg {int /*<<< orphan*/ * cra_type; } ;
struct hash_alg_common {struct crypto_alg base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * setkey; } ;

/* Variables and functions */
 TYPE_1__* __crypto_ahash_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  __crypto_shash_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_ahash_type ; 
 int crypto_shash_alg_has_setkey (int /*<<< orphan*/ ) ; 

bool crypto_hash_alg_has_setkey(struct hash_alg_common *halg)
{
	struct crypto_alg *alg = &halg->base;

	if (alg->cra_type != &crypto_ahash_type)
		return crypto_shash_alg_has_setkey(__crypto_shash_alg(alg));

	return __crypto_ahash_alg(alg)->setkey != NULL;
}