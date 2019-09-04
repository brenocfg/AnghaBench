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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct crypto_alg*) ; 
 struct crypto_alg* crypto_alg_mod_lookup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 

int crypto_has_alg(const char *name, u32 type, u32 mask)
{
	int ret = 0;
	struct crypto_alg *alg = crypto_alg_mod_lookup(name, type, mask);

	if (!IS_ERR(alg)) {
		crypto_mod_put(alg);
		ret = 1;
	}

	return ret;
}