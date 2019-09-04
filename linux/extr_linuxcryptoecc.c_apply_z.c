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
 int /*<<< orphan*/  vli_mod_mult_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_square_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void apply_z(u64 *x1, u64 *y1, u64 *z, u64 *curve_prime,
		    unsigned int ndigits)
{
	u64 t1[ECC_MAX_DIGITS];

	vli_mod_square_fast(t1, z, curve_prime, ndigits);    /* z^2 */
	vli_mod_mult_fast(x1, x1, t1, curve_prime, ndigits); /* x1 * z^2 */
	vli_mod_mult_fast(t1, t1, z, curve_prime, ndigits);  /* z^3 */
	vli_mod_mult_fast(y1, y1, t1, curve_prime, ndigits); /* y1 * z^3 */
}