#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_6__ {unsigned long long intercept; int* msrpm; scalar_t__ vmcb_msrpm; } ;
struct vcpu_svm {int* msrpm; TYPE_3__ nested; TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  msrpm_base_pa; } ;
struct TYPE_5__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_MSR_PROT ; 
 int MSRPM_OFFSETS ; 
 int /*<<< orphan*/  __pa (int*) ; 
 int /*<<< orphan*/  __sme_set (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_read_guest (int /*<<< orphan*/ *,scalar_t__,int*,int) ; 
 int* msrpm_offsets ; 

__attribute__((used)) static bool nested_svm_vmrun_msrpm(struct vcpu_svm *svm)
{
	/*
	 * This function merges the msr permission bitmaps of kvm and the
	 * nested vmcb. It is optimized in that it only merges the parts where
	 * the kvm msr permission bitmap may contain zero bits
	 */
	int i;

	if (!(svm->nested.intercept & (1ULL << INTERCEPT_MSR_PROT)))
		return true;

	for (i = 0; i < MSRPM_OFFSETS; i++) {
		u32 value, p;
		u64 offset;

		if (msrpm_offsets[i] == 0xffffffff)
			break;

		p      = msrpm_offsets[i];
		offset = svm->nested.vmcb_msrpm + (p * 4);

		if (kvm_vcpu_read_guest(&svm->vcpu, offset, &value, 4))
			return false;

		svm->nested.msrpm[p] = svm->msrpm[p] | value;
	}

	svm->vmcb->control.msrpm_base_pa = __sme_set(__pa(svm->nested.msrpm));

	return true;
}