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
typedef  unsigned int u64 ;

/* Variables and functions */
 unsigned int MMIO_GEN_LOW_MASK ; 
 unsigned int MMIO_GEN_LOW_SHIFT ; 
 unsigned int MMIO_SPTE_GEN_HIGH_SHIFT ; 
 unsigned int MMIO_SPTE_GEN_LOW_SHIFT ; 
 unsigned int shadow_mmio_mask ; 

__attribute__((used)) static unsigned int get_mmio_spte_generation(u64 spte)
{
	unsigned int gen;

	spte &= ~shadow_mmio_mask;

	gen = (spte >> MMIO_SPTE_GEN_LOW_SHIFT) & MMIO_GEN_LOW_MASK;
	gen |= (spte >> MMIO_SPTE_GEN_HIGH_SHIFT) << MMIO_GEN_LOW_SHIFT;
	return gen;
}