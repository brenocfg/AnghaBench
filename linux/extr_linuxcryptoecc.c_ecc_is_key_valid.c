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
struct ecc_curve {int /*<<< orphan*/  n; } ;

/* Variables and functions */
 unsigned int ECC_DIGITS_TO_BYTES_SHIFT ; 
 int EINVAL ; 
 struct ecc_curve* ecc_get_curve (unsigned int) ; 
 int vli_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ vli_is_zero (int /*<<< orphan*/  const*,unsigned int) ; 

int ecc_is_key_valid(unsigned int curve_id, unsigned int ndigits,
		     const u64 *private_key, unsigned int private_key_len)
{
	int nbytes;
	const struct ecc_curve *curve = ecc_get_curve(curve_id);

	if (!private_key)
		return -EINVAL;

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	if (private_key_len != nbytes)
		return -EINVAL;

	if (vli_is_zero(private_key, ndigits))
		return -EINVAL;

	/* Make sure the private key is in the range [1, n-1]. */
	if (vli_cmp(curve->n, private_key, ndigits) != 1)
		return -EINVAL;

	return 0;
}