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
typedef  int u64 ;

/* Variables and functions */
 unsigned int MMIO_GEN_LOW_MASK ; 
 int MMIO_GEN_LOW_SHIFT ; 
 unsigned int MMIO_GEN_MASK ; 
 int MMIO_SPTE_GEN_HIGH_SHIFT ; 
 unsigned int MMIO_SPTE_GEN_LOW_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 

__attribute__((used)) static u64 generation_mmio_spte_mask(unsigned int gen)
{
	u64 mask;

	WARN_ON(gen & ~MMIO_GEN_MASK);

	mask = (gen & MMIO_GEN_LOW_MASK) << MMIO_SPTE_GEN_LOW_SHIFT;
	mask |= ((u64)gen >> MMIO_GEN_LOW_SHIFT) << MMIO_SPTE_GEN_HIGH_SHIFT;
	return mask;
}