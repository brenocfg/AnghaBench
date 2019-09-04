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

/* Variables and functions */
 int NFORCE2_PLL (unsigned char,unsigned char) ; 
 unsigned int nforce2_calc_fsb (int) ; 

__attribute__((used)) static int nforce2_calc_pll(unsigned int fsb)
{
	unsigned char xmul, xdiv;
	unsigned char mul = 0, div = 0;
	int tried = 0;

	/* Try to calculate multiplier and divider up to 4 times */
	while (((mul == 0) || (div == 0)) && (tried <= 3)) {
		for (xdiv = 2; xdiv <= 0x80; xdiv++)
			for (xmul = 1; xmul <= 0xfe; xmul++)
				if (nforce2_calc_fsb(NFORCE2_PLL(xmul, xdiv)) ==
				    fsb + tried) {
					mul = xmul;
					div = xdiv;
				}
		tried++;
	}

	if ((mul == 0) || (div == 0))
		return -1;

	return NFORCE2_PLL(mul, div);
}