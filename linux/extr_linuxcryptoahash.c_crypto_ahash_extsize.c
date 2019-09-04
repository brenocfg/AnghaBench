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
struct crypto_shash {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ahash_type ; 
 unsigned int crypto_alg_extsize (struct crypto_alg*) ; 

__attribute__((used)) static unsigned int crypto_ahash_extsize(struct crypto_alg *alg)
{
	if (alg->cra_type != &crypto_ahash_type)
		return sizeof(struct crypto_shash *);

	return crypto_alg_extsize(alg);
}