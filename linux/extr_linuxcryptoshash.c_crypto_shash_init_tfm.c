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
struct shash_alg {int /*<<< orphan*/  descsize; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_shash {int /*<<< orphan*/  descsize; } ;

/* Variables and functions */
 struct crypto_shash* __crypto_shash_cast (struct crypto_tfm*) ; 
 struct shash_alg* crypto_shash_alg (struct crypto_shash*) ; 
 int /*<<< orphan*/  shash_set_needkey (struct crypto_shash*,struct shash_alg*) ; 

__attribute__((used)) static int crypto_shash_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_shash *hash = __crypto_shash_cast(tfm);
	struct shash_alg *alg = crypto_shash_alg(hash);

	hash->descsize = alg->descsize;

	shash_set_needkey(hash, alg);

	return 0;
}