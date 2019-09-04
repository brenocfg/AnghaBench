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
struct vmcs12 {int /*<<< orphan*/  msr_bitmap; } ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {unsigned long* msr_bitmap; } ;
struct TYPE_5__ {TYPE_1__ vmcs02; } ;
struct TYPE_6__ {TYPE_2__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_EOI ; 
 int /*<<< orphan*/  APIC_SELF_IPI ; 
 int /*<<< orphan*/  APIC_TASKPRI ; 
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  CPU_BASED_USE_MSR_BITMAPS ; 
 int /*<<< orphan*/  MSR_IA32_PRED_CMD ; 
 int /*<<< orphan*/  MSR_IA32_SPEC_CTRL ; 
 int MSR_TYPE_R ; 
 int MSR_TYPE_W ; 
 int /*<<< orphan*/  X2APIC_MSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_vmx_msr_bitmap () ; 
 int /*<<< orphan*/  enable_x2apic_msr_intercepts (unsigned long*) ; 
 scalar_t__ is_error_page (struct page*) ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 struct page* kvm_vcpu_gpa_to_page (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msr_write_intercepted_l01 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has_apic_reg_virt (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vid (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_virt_x2apic_mode (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_vmx_disable_intercept_for_msr (unsigned long*,unsigned long*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool nested_vmx_prepare_msr_bitmap(struct kvm_vcpu *vcpu,
						 struct vmcs12 *vmcs12)
{
	int msr;
	struct page *page;
	unsigned long *msr_bitmap_l1;
	unsigned long *msr_bitmap_l0 = to_vmx(vcpu)->nested.vmcs02.msr_bitmap;
	/*
	 * pred_cmd & spec_ctrl are trying to verify two things:
	 *
	 * 1. L0 gave a permission to L1 to actually passthrough the MSR. This
	 *    ensures that we do not accidentally generate an L02 MSR bitmap
	 *    from the L12 MSR bitmap that is too permissive.
	 * 2. That L1 or L2s have actually used the MSR. This avoids
	 *    unnecessarily merging of the bitmap if the MSR is unused. This
	 *    works properly because we only update the L01 MSR bitmap lazily.
	 *    So even if L0 should pass L1 these MSRs, the L01 bitmap is only
	 *    updated to reflect this when L1 (or its L2s) actually write to
	 *    the MSR.
	 */
	bool pred_cmd = !msr_write_intercepted_l01(vcpu, MSR_IA32_PRED_CMD);
	bool spec_ctrl = !msr_write_intercepted_l01(vcpu, MSR_IA32_SPEC_CTRL);

	/* Nothing to do if the MSR bitmap is not in use.  */
	if (!cpu_has_vmx_msr_bitmap() ||
	    !nested_cpu_has(vmcs12, CPU_BASED_USE_MSR_BITMAPS))
		return false;

	if (!nested_cpu_has_virt_x2apic_mode(vmcs12) &&
	    !pred_cmd && !spec_ctrl)
		return false;

	page = kvm_vcpu_gpa_to_page(vcpu, vmcs12->msr_bitmap);
	if (is_error_page(page))
		return false;

	msr_bitmap_l1 = (unsigned long *)kmap(page);

	/*
	 * To keep the control flow simple, pay eight 8-byte writes (sixteen
	 * 4-byte writes on 32-bit systems) up front to enable intercepts for
	 * the x2APIC MSR range and selectively disable them below.
	 */
	enable_x2apic_msr_intercepts(msr_bitmap_l0);

	if (nested_cpu_has_virt_x2apic_mode(vmcs12)) {
		if (nested_cpu_has_apic_reg_virt(vmcs12)) {
			/*
			 * L0 need not intercept reads for MSRs between 0x800
			 * and 0x8ff, it just lets the processor take the value
			 * from the virtual-APIC page; take those 256 bits
			 * directly from the L1 bitmap.
			 */
			for (msr = 0x800; msr <= 0x8ff; msr += BITS_PER_LONG) {
				unsigned word = msr / BITS_PER_LONG;

				msr_bitmap_l0[word] = msr_bitmap_l1[word];
			}
		}

		nested_vmx_disable_intercept_for_msr(
			msr_bitmap_l1, msr_bitmap_l0,
			X2APIC_MSR(APIC_TASKPRI),
			MSR_TYPE_R | MSR_TYPE_W);

		if (nested_cpu_has_vid(vmcs12)) {
			nested_vmx_disable_intercept_for_msr(
				msr_bitmap_l1, msr_bitmap_l0,
				X2APIC_MSR(APIC_EOI),
				MSR_TYPE_W);
			nested_vmx_disable_intercept_for_msr(
				msr_bitmap_l1, msr_bitmap_l0,
				X2APIC_MSR(APIC_SELF_IPI),
				MSR_TYPE_W);
		}
	}

	if (spec_ctrl)
		nested_vmx_disable_intercept_for_msr(
					msr_bitmap_l1, msr_bitmap_l0,
					MSR_IA32_SPEC_CTRL,
					MSR_TYPE_R | MSR_TYPE_W);

	if (pred_cmd)
		nested_vmx_disable_intercept_for_msr(
					msr_bitmap_l1, msr_bitmap_l0,
					MSR_IA32_PRED_CMD,
					MSR_TYPE_W);

	kunmap(page);
	kvm_release_page_clean(page);

	return true;
}