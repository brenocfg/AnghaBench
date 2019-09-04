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
typedef  int u8 ;
struct TYPE_2__ {int x86_phys_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  rsvd_bits (int,int) ; 
 scalar_t__ shadow_acc_track_mask ; 
 scalar_t__ shadow_accessed_mask ; 
 scalar_t__ shadow_dirty_mask ; 
 scalar_t__ shadow_mmio_mask ; 
 int /*<<< orphan*/  shadow_nonpresent_or_rsvd_lower_gfn_mask ; 
 int /*<<< orphan*/  shadow_nonpresent_or_rsvd_mask ; 
 int shadow_nonpresent_or_rsvd_mask_len ; 
 scalar_t__ shadow_nx_mask ; 
 scalar_t__ shadow_present_mask ; 
 scalar_t__ shadow_user_mask ; 
 scalar_t__ shadow_x_mask ; 

__attribute__((used)) static void kvm_mmu_reset_all_pte_masks(void)
{
	u8 low_phys_bits;

	shadow_user_mask = 0;
	shadow_accessed_mask = 0;
	shadow_dirty_mask = 0;
	shadow_nx_mask = 0;
	shadow_x_mask = 0;
	shadow_mmio_mask = 0;
	shadow_present_mask = 0;
	shadow_acc_track_mask = 0;

	/*
	 * If the CPU has 46 or less physical address bits, then set an
	 * appropriate mask to guard against L1TF attacks. Otherwise, it is
	 * assumed that the CPU is not vulnerable to L1TF.
	 */
	low_phys_bits = boot_cpu_data.x86_phys_bits;
	if (boot_cpu_data.x86_phys_bits <
	    52 - shadow_nonpresent_or_rsvd_mask_len) {
		shadow_nonpresent_or_rsvd_mask =
			rsvd_bits(boot_cpu_data.x86_phys_bits -
				  shadow_nonpresent_or_rsvd_mask_len,
				  boot_cpu_data.x86_phys_bits - 1);
		low_phys_bits -= shadow_nonpresent_or_rsvd_mask_len;
	}
	shadow_nonpresent_or_rsvd_lower_gfn_mask =
		GENMASK_ULL(low_phys_bits - 1, PAGE_SHIFT);
}