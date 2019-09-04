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
typedef  int gva_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static int tlb0_set_base(gva_t addr, int sets, int ways)
{
	int set_base;

	set_base = (addr >> PAGE_SHIFT) & (sets - 1);
	set_base *= ways;

	return set_base;
}