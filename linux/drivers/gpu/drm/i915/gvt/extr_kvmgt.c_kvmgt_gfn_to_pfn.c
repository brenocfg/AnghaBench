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
struct kvmgt_guest_info {int /*<<< orphan*/  kvm; } ;
typedef  unsigned long kvm_pfn_t ;

/* Variables and functions */
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 unsigned long gfn_to_pfn (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_valid (unsigned long) ; 
 scalar_t__ is_error_noslot_pfn (unsigned long) ; 

__attribute__((used)) static unsigned long kvmgt_gfn_to_pfn(unsigned long handle, unsigned long gfn)
{
	struct kvmgt_guest_info *info;
	kvm_pfn_t pfn;

	if (!handle_valid(handle))
		return INTEL_GVT_INVALID_ADDR;

	info = (struct kvmgt_guest_info *)handle;

	pfn = gfn_to_pfn(info->kvm, gfn);
	if (is_error_noslot_pfn(pfn))
		return INTEL_GVT_INVALID_ADDR;

	return pfn;
}