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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_cpuid_entry2 {int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 struct kvm_cpuid_entry2* check_cpuid_limit (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool kvm_cpuid(struct kvm_vcpu *vcpu, u32 *eax, u32 *ebx,
	       u32 *ecx, u32 *edx, bool check_limit)
{
	u32 function = *eax, index = *ecx;
	struct kvm_cpuid_entry2 *best;
	bool entry_found = true;

	best = kvm_find_cpuid_entry(vcpu, function, index);

	if (!best) {
		entry_found = false;
		if (!check_limit)
			goto out;

		best = check_cpuid_limit(vcpu, function, index);
	}

out:
	if (best) {
		*eax = best->eax;
		*ebx = best->ebx;
		*ecx = best->ecx;
		*edx = best->edx;
	} else
		*eax = *ebx = *ecx = *edx = 0;
	trace_kvm_cpuid(function, *eax, *ebx, *ecx, *edx, entry_found);
	return entry_found;
}