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
struct crypto_alg {int /*<<< orphan*/  cra_flags; int /*<<< orphan*/ * cra_type; } ;
struct rng_alg {int seedsize; struct crypto_alg base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_RNG ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_rng_type ; 

int crypto_register_rng(struct rng_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	if (alg->seedsize > PAGE_SIZE / 8)
		return -EINVAL;

	base->cra_type = &crypto_rng_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_RNG;

	return crypto_register_alg(base);
}