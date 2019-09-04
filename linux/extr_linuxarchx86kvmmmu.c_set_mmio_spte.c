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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_noslot_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_mmio_spte (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, gfn_t gfn,
			  kvm_pfn_t pfn, unsigned access)
{
	if (unlikely(is_noslot_pfn(pfn))) {
		mark_mmio_spte(vcpu, sptep, gfn, access);
		return true;
	}

	return false;
}