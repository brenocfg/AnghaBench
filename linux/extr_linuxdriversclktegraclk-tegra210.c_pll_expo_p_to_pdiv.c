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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int PLL_EXPO_PDIV_MAX ; 
 int ffs (int) ; 
 int fls (int) ; 

__attribute__((used)) static u32 pll_expo_p_to_pdiv(u32 p, u32 *pdiv)
{
	if (p) {
		u32 i = fls(p);

		if (i == ffs(p))
			i--;

		if (i <= PLL_EXPO_PDIV_MAX) {
			if (pdiv)
				*pdiv = i;
			return 1 << i;
		}
	}
	return -EINVAL;
}