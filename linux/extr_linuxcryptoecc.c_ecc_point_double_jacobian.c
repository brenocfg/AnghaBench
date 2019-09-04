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
typedef  int u64 ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int vli_add (int*,int*,int*,unsigned int) ; 
 scalar_t__ vli_is_zero (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_add (int*,int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_mult_fast (int*,int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_square_fast (int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_sub (int*,int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_rshift1 (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int*,int*,unsigned int) ; 
 scalar_t__ vli_test_bit (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecc_point_double_jacobian(u64 *x1, u64 *y1, u64 *z1,
				      u64 *curve_prime, unsigned int ndigits)
{
	/* t1 = x, t2 = y, t3 = z */
	u64 t4[ECC_MAX_DIGITS];
	u64 t5[ECC_MAX_DIGITS];

	if (vli_is_zero(z1, ndigits))
		return;

	/* t4 = y1^2 */
	vli_mod_square_fast(t4, y1, curve_prime, ndigits);
	/* t5 = x1*y1^2 = A */
	vli_mod_mult_fast(t5, x1, t4, curve_prime, ndigits);
	/* t4 = y1^4 */
	vli_mod_square_fast(t4, t4, curve_prime, ndigits);
	/* t2 = y1*z1 = z3 */
	vli_mod_mult_fast(y1, y1, z1, curve_prime, ndigits);
	/* t3 = z1^2 */
	vli_mod_square_fast(z1, z1, curve_prime, ndigits);

	/* t1 = x1 + z1^2 */
	vli_mod_add(x1, x1, z1, curve_prime, ndigits);
	/* t3 = 2*z1^2 */
	vli_mod_add(z1, z1, z1, curve_prime, ndigits);
	/* t3 = x1 - z1^2 */
	vli_mod_sub(z1, x1, z1, curve_prime, ndigits);
	/* t1 = x1^2 - z1^4 */
	vli_mod_mult_fast(x1, x1, z1, curve_prime, ndigits);

	/* t3 = 2*(x1^2 - z1^4) */
	vli_mod_add(z1, x1, x1, curve_prime, ndigits);
	/* t1 = 3*(x1^2 - z1^4) */
	vli_mod_add(x1, x1, z1, curve_prime, ndigits);
	if (vli_test_bit(x1, 0)) {
		u64 carry = vli_add(x1, x1, curve_prime, ndigits);

		vli_rshift1(x1, ndigits);
		x1[ndigits - 1] |= carry << 63;
	} else {
		vli_rshift1(x1, ndigits);
	}
	/* t1 = 3/2*(x1^2 - z1^4) = B */

	/* t3 = B^2 */
	vli_mod_square_fast(z1, x1, curve_prime, ndigits);
	/* t3 = B^2 - A */
	vli_mod_sub(z1, z1, t5, curve_prime, ndigits);
	/* t3 = B^2 - 2A = x3 */
	vli_mod_sub(z1, z1, t5, curve_prime, ndigits);
	/* t5 = A - x3 */
	vli_mod_sub(t5, t5, z1, curve_prime, ndigits);
	/* t1 = B * (A - x3) */
	vli_mod_mult_fast(x1, x1, t5, curve_prime, ndigits);
	/* t4 = B * (A - x3) - y1^4 = y3 */
	vli_mod_sub(t4, x1, t4, curve_prime, ndigits);

	vli_set(x1, z1, ndigits);
	vli_set(z1, y1, ndigits);
	vli_set(y1, t4, ndigits);
}