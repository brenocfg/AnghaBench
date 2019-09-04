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
typedef  union ieee754dp {int dummy; } ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXDP ; 
 int /*<<< orphan*/  EXPLODEXDP ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int xc ; 
 int /*<<< orphan*/  xs ; 

int ieee754dp_2008class(union ieee754dp x)
{
	COMPXDP;

	EXPLODEXDP;

	/*
	 * 10 bit mask as follows:
	 *
	 * bit0 = SNAN
	 * bit1 = QNAN
	 * bit2 = -INF
	 * bit3 = -NORM
	 * bit4 = -DNORM
	 * bit5 = -ZERO
	 * bit6 = INF
	 * bit7 = NORM
	 * bit8 = DNORM
	 * bit9 = ZERO
	 */

	switch(xc) {
	case IEEE754_CLASS_SNAN:
		return 0x01;
	case IEEE754_CLASS_QNAN:
		return 0x02;
	case IEEE754_CLASS_INF:
		return 0x04 << (xs ? 0 : 4);
	case IEEE754_CLASS_NORM:
		return 0x08 << (xs ? 0 : 4);
	case IEEE754_CLASS_DNORM:
		return 0x10 << (xs ? 0 : 4);
	case IEEE754_CLASS_ZERO:
		return 0x20 << (xs ? 0 : 4);
	default:
		pr_err("Unknown class: %d\n", xc);
		return 0;
	}
}