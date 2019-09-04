#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_2__ {int x86_phys_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  kvm_mmu_set_mmio_spte_mask (unsigned long long,unsigned long long) ; 

__attribute__((used)) static void kvm_set_mmio_spte_mask(void)
{
	u64 mask;
	int maxphyaddr = boot_cpu_data.x86_phys_bits;

	/*
	 * Set the reserved bits and the present bit of an paging-structure
	 * entry to generate page fault with PFER.RSV = 1.
	 */

	/*
	 * Mask the uppermost physical address bit, which would be reserved as
	 * long as the supported physical address width is less than 52.
	 */
	mask = 1ull << 51;

	/* Set the present bit. */
	mask |= 1ull;

	/*
	 * If reserved bit is not supported, clear the present bit to disable
	 * mmio page fault.
	 */
	if (IS_ENABLED(CONFIG_X86_64) && maxphyaddr == 52)
		mask &= ~1ull;

	kvm_mmu_set_mmio_spte_mask(mask, mask);
}