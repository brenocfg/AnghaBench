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
typedef  int /*<<< orphan*/  u8 ;
typedef  int s32 ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int SPS30_MAX_PM ; 
 int get_unaligned_be32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static s32 sps30_float_to_int_clamped(const u8 *fp)
{
	int val = get_unaligned_be32(fp);
	int mantissa = val & GENMASK(22, 0);
	/* this is fine since passed float is always non-negative */
	int exp = val >> 23;
	int fraction, shift;

	/* special case 0 */
	if (!exp && !mantissa)
		return 0;

	exp -= 127;
	if (exp < 0) {
		/* return values ranging from 1 to 99 */
		return ((((1 << 23) + mantissa) * 100) >> 23) >> (-exp);
	}

	/* return values ranging from 100 to 300000 */
	shift = 23 - exp;
	val = (1 << exp) + (mantissa >> shift);
	if (val >= SPS30_MAX_PM)
		return SPS30_MAX_PM * 100;

	fraction = mantissa & GENMASK(shift - 1, 0);

	return val * 100 + ((fraction * 100) >> shift);
}