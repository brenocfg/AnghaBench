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
 int /*<<< orphan*/  __tlbiel_va (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long mmu_get_ap (unsigned long) ; 

__attribute__((used)) static inline void _tlbiel_va(unsigned long va, unsigned long pid,
			      unsigned long psize, unsigned long ric)
{
	unsigned long ap = mmu_get_ap(psize);

	asm volatile("ptesync": : :"memory");
	__tlbiel_va(va, pid, ap, ric);
	asm volatile("ptesync": : :"memory");
}