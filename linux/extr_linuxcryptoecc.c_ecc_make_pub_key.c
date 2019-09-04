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
struct ecc_point {int /*<<< orphan*/  const* y; int /*<<< orphan*/  const* x; } ;
struct ecc_curve {int /*<<< orphan*/  g; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EAGAIN ; 
 int ECC_MAX_DIGITS ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ecc_point* ecc_alloc_point (unsigned int) ; 
 int /*<<< orphan*/  ecc_free_point (struct ecc_point*) ; 
 struct ecc_curve* ecc_get_curve (unsigned int) ; 
 scalar_t__ ecc_point_is_zero (struct ecc_point*) ; 
 int /*<<< orphan*/  ecc_point_mult (struct ecc_point*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ecc_curve const*,unsigned int) ; 
 int /*<<< orphan*/  ecc_swap_digits (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int) ; 

int ecc_make_pub_key(unsigned int curve_id, unsigned int ndigits,
		     const u64 *private_key, u64 *public_key)
{
	int ret = 0;
	struct ecc_point *pk;
	u64 priv[ECC_MAX_DIGITS];
	const struct ecc_curve *curve = ecc_get_curve(curve_id);

	if (!private_key || !curve || ndigits > ARRAY_SIZE(priv)) {
		ret = -EINVAL;
		goto out;
	}

	ecc_swap_digits(private_key, priv, ndigits);

	pk = ecc_alloc_point(ndigits);
	if (!pk) {
		ret = -ENOMEM;
		goto out;
	}

	ecc_point_mult(pk, &curve->g, priv, NULL, curve, ndigits);
	if (ecc_point_is_zero(pk)) {
		ret = -EAGAIN;
		goto err_free_point;
	}

	ecc_swap_digits(pk->x, public_key, ndigits);
	ecc_swap_digits(pk->y, &public_key[ndigits], ndigits);

err_free_point:
	ecc_free_point(pk);
out:
	return ret;
}