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
typedef  int /*<<< orphan*/  uint64_t ;
struct bkey_float {int exponent; } ;
struct bkey {int /*<<< orphan*/  low; } ;

/* Variables and functions */
 unsigned int BKEY_MANTISSA_MASK ; 
 unsigned int shrd128 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static inline unsigned int bfloat_mantissa(const struct bkey *k,
				       struct bkey_float *f)
{
	const uint64_t *p = &k->low - (f->exponent >> 6);

	return shrd128(p[-1], p[0], f->exponent & 63) & BKEY_MANTISSA_MASK;
}