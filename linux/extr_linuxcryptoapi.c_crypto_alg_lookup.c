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
typedef  int u32 ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_TESTED ; 
 int /*<<< orphan*/  ELIBBAD ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct crypto_alg* __crypto_alg_lookup (char const*,int,int) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  crypto_is_larval (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct crypto_alg *crypto_alg_lookup(const char *name, u32 type,
					    u32 mask)
{
	struct crypto_alg *alg;
	u32 test = 0;

	if (!((type | mask) & CRYPTO_ALG_TESTED))
		test |= CRYPTO_ALG_TESTED;

	down_read(&crypto_alg_sem);
	alg = __crypto_alg_lookup(name, type | test, mask | test);
	if (!alg && test) {
		alg = __crypto_alg_lookup(name, type, mask);
		if (alg && !crypto_is_larval(alg)) {
			/* Test failed */
			crypto_mod_put(alg);
			alg = ERR_PTR(-ELIBBAD);
		}
	}
	up_read(&crypto_alg_sem);

	return alg;
}