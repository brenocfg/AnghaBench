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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int EINVAL ; 
 int RET_PF_EMULATE ; 
 int RET_PF_INVALID ; 
 int RET_PF_RETRY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  check_mmio_spte (struct kvm_vcpu*,scalar_t__) ; 
 unsigned int get_mmio_spte_access (scalar_t__) ; 
 int /*<<< orphan*/  get_mmio_spte_gfn (scalar_t__) ; 
 scalar_t__ is_mmio_spte (scalar_t__) ; 
 scalar_t__ mmio_info_in_cache (struct kvm_vcpu*,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_handle_mmio_page_fault (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vcpu_cache_mmio_info (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int walk_shadow_page_get_mmio_spte (struct kvm_vcpu*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int handle_mmio_page_fault(struct kvm_vcpu *vcpu, u64 addr, bool direct)
{
	u64 spte;
	bool reserved;

	if (mmio_info_in_cache(vcpu, addr, direct))
		return RET_PF_EMULATE;

	reserved = walk_shadow_page_get_mmio_spte(vcpu, addr, &spte);
	if (WARN_ON(reserved))
		return -EINVAL;

	if (is_mmio_spte(spte)) {
		gfn_t gfn = get_mmio_spte_gfn(spte);
		unsigned access = get_mmio_spte_access(spte);

		if (!check_mmio_spte(vcpu, spte))
			return RET_PF_INVALID;

		if (direct)
			addr = 0;

		trace_handle_mmio_page_fault(addr, gfn, access);
		vcpu_cache_mmio_info(vcpu, addr, gfn, access);
		return RET_PF_EMULATE;
	}

	/*
	 * If the page table is zapped by other cpus, let CPU fault again on
	 * the address.
	 */
	return RET_PF_RETRY;
}