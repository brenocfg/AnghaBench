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
 scalar_t__ CKSEG1ADDR (scalar_t__) ; 
 scalar_t__ HQ2_MYSTERY_OFFS ; 
 int /*<<< orphan*/  get_dbe (int,int*) ; 

__attribute__((used)) static int ip22_is_gr2(unsigned long addr)
{
	u32 tmp;
	u32 *ptr;

	/* HQ2 only allows 32bit accesses */
	ptr = (void *)CKSEG1ADDR(addr + HQ2_MYSTERY_OFFS);
	if (!get_dbe(tmp, ptr)) {
		if (tmp == 0xdeadbeef)
			return 1;
	}
	return 0;
}