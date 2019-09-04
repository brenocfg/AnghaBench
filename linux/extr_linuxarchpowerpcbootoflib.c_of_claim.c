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
typedef  int prom_arg_t ;

/* Variables and functions */
 scalar_t__ check_of_version () ; 
 int /*<<< orphan*/  chosen_mmu ; 
 int /*<<< orphan*/  memory ; 
 scalar_t__ need_map ; 
 unsigned int of_call_prom (char*,int,int,...) ; 
 int of_call_prom_ret (char*,int,int,int*,char*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 

unsigned int of_claim(unsigned long virt, unsigned long size,
		      unsigned long align)
{
	int ret;
	prom_arg_t result;

	if (need_map < 0)
		need_map = check_of_version();
	if (align || !need_map)
		return of_call_prom("claim", 3, 1, virt, size, align);

	ret = of_call_prom_ret("call-method", 5, 2, &result, "claim", memory,
			       align, size, virt);
	if (ret != 0 || result == -1)
		return  -1;
	ret = of_call_prom_ret("call-method", 5, 2, &result, "claim", chosen_mmu,
			       align, size, virt);
	/* 0x12 == coherent + read/write */
	ret = of_call_prom("call-method", 6, 1, "map", chosen_mmu,
			   0x12, size, virt, virt);
	return virt;
}