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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  vli_mmod_fast_192 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vli_mmod_fast_256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vli_mmod_fast(u64 *result, u64 *product,
			  const u64 *curve_prime, unsigned int ndigits)
{
	u64 tmp[2 * ECC_MAX_DIGITS];

	switch (ndigits) {
	case 3:
		vli_mmod_fast_192(result, product, curve_prime, tmp);
		break;
	case 4:
		vli_mmod_fast_256(result, product, curve_prime, tmp);
		break;
	default:
		pr_err("unsupports digits size!\n");
		return false;
	}

	return true;
}