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
typedef  int const u64 ;
typedef  int const u32 ;

/* Variables and functions */
 int NUM_PTE (unsigned int) ; 
 int const PAGE_SHIFT ; 

__attribute__((used)) static inline u32 i915_pte_index(u64 address, unsigned int pde_shift)
{
	const u32 mask = NUM_PTE(pde_shift) - 1;

	return (address >> PAGE_SHIFT) & mask;
}