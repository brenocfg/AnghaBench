#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vmcs12 {unsigned long long xss_exit_bitmap; unsigned long long eoi_exit_bitmap0; unsigned long long eoi_exit_bitmap1; unsigned long long eoi_exit_bitmap2; unsigned long long eoi_exit_bitmap3; int vm_entry_controls; unsigned long long guest_bndcfgs; unsigned long long guest_pdptr0; unsigned long long guest_pdptr1; unsigned long long guest_pdptr2; unsigned long long guest_pdptr3; int /*<<< orphan*/  page_fault_error_code_match; int /*<<< orphan*/  page_fault_error_code_mask; int /*<<< orphan*/  guest_sysenter_eip; int /*<<< orphan*/  guest_sysenter_esp; int /*<<< orphan*/  guest_pending_dbg_exceptions; int /*<<< orphan*/  guest_sysenter_cs; int /*<<< orphan*/  guest_idtr_base; int /*<<< orphan*/  guest_gdtr_base; int /*<<< orphan*/  guest_tr_base; int /*<<< orphan*/  guest_ldtr_base; int /*<<< orphan*/  guest_gs_base; int /*<<< orphan*/  guest_fs_base; int /*<<< orphan*/  guest_ds_base; int /*<<< orphan*/  guest_ss_base; int /*<<< orphan*/  guest_tr_ar_bytes; int /*<<< orphan*/  guest_ldtr_ar_bytes; int /*<<< orphan*/  guest_gs_ar_bytes; int /*<<< orphan*/  guest_fs_ar_bytes; int /*<<< orphan*/  guest_ds_ar_bytes; int /*<<< orphan*/  guest_ss_ar_bytes; int /*<<< orphan*/  guest_es_ar_bytes; int /*<<< orphan*/  guest_idtr_limit; int /*<<< orphan*/  guest_gdtr_limit; int /*<<< orphan*/  guest_tr_limit; int /*<<< orphan*/  guest_ldtr_limit; int /*<<< orphan*/  guest_gs_limit; int /*<<< orphan*/  guest_fs_limit; int /*<<< orphan*/  guest_ds_limit; int /*<<< orphan*/  guest_ss_limit; int /*<<< orphan*/  guest_es_limit; scalar_t__ guest_tr_selector; scalar_t__ guest_ldtr_selector; scalar_t__ guest_gs_selector; scalar_t__ guest_fs_selector; scalar_t__ guest_ds_selector; scalar_t__ guest_ss_selector; scalar_t__ guest_es_selector; } ;
struct TYPE_9__ {int /*<<< orphan*/  msr_bitmap; } ;
struct TYPE_10__ {unsigned long long vmcs01_guest_bndcfgs; TYPE_4__ vmcs02; scalar_t__ vpid02; scalar_t__ nested_run_pending; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; int /*<<< orphan*/  nr; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  nr; } ;
struct TYPE_8__ {TYPE_2__ guest; TYPE_1__ host; } ;
struct vcpu_vmx {TYPE_5__ nested; scalar_t__ vpid; TYPE_3__ msr_autoload; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOI_EXIT_BITMAP0 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP1 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP2 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP3 ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_DS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_DS_BASE ; 
 int /*<<< orphan*/  GUEST_DS_LIMIT ; 
 int /*<<< orphan*/  GUEST_DS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_ES_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_ES_LIMIT ; 
 int /*<<< orphan*/  GUEST_ES_SELECTOR ; 
 int /*<<< orphan*/  GUEST_FS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_FS_BASE ; 
 int /*<<< orphan*/  GUEST_FS_LIMIT ; 
 int /*<<< orphan*/  GUEST_FS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_GDTR_BASE ; 
 int /*<<< orphan*/  GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_GS_BASE ; 
 int /*<<< orphan*/  GUEST_GS_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_IDTR_BASE ; 
 int /*<<< orphan*/  GUEST_IDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_LDTR_BASE ; 
 int /*<<< orphan*/  GUEST_LDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_SELECTOR ; 
 int /*<<< orphan*/  GUEST_PDPTR0 ; 
 int /*<<< orphan*/  GUEST_PDPTR1 ; 
 int /*<<< orphan*/  GUEST_PDPTR2 ; 
 int /*<<< orphan*/  GUEST_PDPTR3 ; 
 int /*<<< orphan*/  GUEST_PENDING_DBG_EXCEPTIONS ; 
 int /*<<< orphan*/  GUEST_SS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_SS_BASE ; 
 int /*<<< orphan*/  GUEST_SS_LIMIT ; 
 int /*<<< orphan*/  GUEST_SS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_SYSENTER_CS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_EIP ; 
 int /*<<< orphan*/  GUEST_SYSENTER_ESP ; 
 int /*<<< orphan*/  GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_TR_BASE ; 
 int /*<<< orphan*/  GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  GUEST_TR_SELECTOR ; 
 int /*<<< orphan*/  MSR_BITMAP ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MASK ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MATCH ; 
 scalar_t__ POSTED_INTR_NESTED_VECTOR ; 
 int /*<<< orphan*/  POSTED_INTR_NV ; 
 int /*<<< orphan*/  VIRTUAL_PROCESSOR_ID ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int VM_ENTRY_LOAD_BNDCFGS ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_COUNT ; 
 int /*<<< orphan*/  VM_FUNCTION_CONTROL ; 
 int /*<<< orphan*/  XSS_EXIT_BITMAP ; 
 unsigned long long __pa (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_vmx_apicv () ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 scalar_t__ cpu_has_vmx_posted_intr () ; 
 scalar_t__ cpu_has_vmx_vmfunc () ; 
 scalar_t__ enable_ept ; 
 scalar_t__ enable_vpid ; 
 scalar_t__ kvm_mpx_supported () ; 
 scalar_t__ nested_cpu_has_vpid (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_xsaves (struct vmcs12*) ; 
 int /*<<< orphan*/  set_cr4_guest_host_mask (struct vcpu_vmx*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_constant_host_state (struct vcpu_vmx*) ; 

__attribute__((used)) static void prepare_vmcs02_full(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	vmcs_write16(GUEST_ES_SELECTOR, vmcs12->guest_es_selector);
	vmcs_write16(GUEST_SS_SELECTOR, vmcs12->guest_ss_selector);
	vmcs_write16(GUEST_DS_SELECTOR, vmcs12->guest_ds_selector);
	vmcs_write16(GUEST_FS_SELECTOR, vmcs12->guest_fs_selector);
	vmcs_write16(GUEST_GS_SELECTOR, vmcs12->guest_gs_selector);
	vmcs_write16(GUEST_LDTR_SELECTOR, vmcs12->guest_ldtr_selector);
	vmcs_write16(GUEST_TR_SELECTOR, vmcs12->guest_tr_selector);
	vmcs_write32(GUEST_ES_LIMIT, vmcs12->guest_es_limit);
	vmcs_write32(GUEST_SS_LIMIT, vmcs12->guest_ss_limit);
	vmcs_write32(GUEST_DS_LIMIT, vmcs12->guest_ds_limit);
	vmcs_write32(GUEST_FS_LIMIT, vmcs12->guest_fs_limit);
	vmcs_write32(GUEST_GS_LIMIT, vmcs12->guest_gs_limit);
	vmcs_write32(GUEST_LDTR_LIMIT, vmcs12->guest_ldtr_limit);
	vmcs_write32(GUEST_TR_LIMIT, vmcs12->guest_tr_limit);
	vmcs_write32(GUEST_GDTR_LIMIT, vmcs12->guest_gdtr_limit);
	vmcs_write32(GUEST_IDTR_LIMIT, vmcs12->guest_idtr_limit);
	vmcs_write32(GUEST_ES_AR_BYTES, vmcs12->guest_es_ar_bytes);
	vmcs_write32(GUEST_SS_AR_BYTES, vmcs12->guest_ss_ar_bytes);
	vmcs_write32(GUEST_DS_AR_BYTES, vmcs12->guest_ds_ar_bytes);
	vmcs_write32(GUEST_FS_AR_BYTES, vmcs12->guest_fs_ar_bytes);
	vmcs_write32(GUEST_GS_AR_BYTES, vmcs12->guest_gs_ar_bytes);
	vmcs_write32(GUEST_LDTR_AR_BYTES, vmcs12->guest_ldtr_ar_bytes);
	vmcs_write32(GUEST_TR_AR_BYTES, vmcs12->guest_tr_ar_bytes);
	vmcs_writel(GUEST_SS_BASE, vmcs12->guest_ss_base);
	vmcs_writel(GUEST_DS_BASE, vmcs12->guest_ds_base);
	vmcs_writel(GUEST_FS_BASE, vmcs12->guest_fs_base);
	vmcs_writel(GUEST_GS_BASE, vmcs12->guest_gs_base);
	vmcs_writel(GUEST_LDTR_BASE, vmcs12->guest_ldtr_base);
	vmcs_writel(GUEST_TR_BASE, vmcs12->guest_tr_base);
	vmcs_writel(GUEST_GDTR_BASE, vmcs12->guest_gdtr_base);
	vmcs_writel(GUEST_IDTR_BASE, vmcs12->guest_idtr_base);

	vmcs_write32(GUEST_SYSENTER_CS, vmcs12->guest_sysenter_cs);
	vmcs_writel(GUEST_PENDING_DBG_EXCEPTIONS,
		vmcs12->guest_pending_dbg_exceptions);
	vmcs_writel(GUEST_SYSENTER_ESP, vmcs12->guest_sysenter_esp);
	vmcs_writel(GUEST_SYSENTER_EIP, vmcs12->guest_sysenter_eip);

	if (nested_cpu_has_xsaves(vmcs12))
		vmcs_write64(XSS_EXIT_BITMAP, vmcs12->xss_exit_bitmap);
	vmcs_write64(VMCS_LINK_POINTER, -1ull);

	if (cpu_has_vmx_posted_intr())
		vmcs_write16(POSTED_INTR_NV, POSTED_INTR_NESTED_VECTOR);

	/*
	 * Whether page-faults are trapped is determined by a combination of
	 * 3 settings: PFEC_MASK, PFEC_MATCH and EXCEPTION_BITMAP.PF.
	 * If enable_ept, L0 doesn't care about page faults and we should
	 * set all of these to L1's desires. However, if !enable_ept, L0 does
	 * care about (at least some) page faults, and because it is not easy
	 * (if at all possible?) to merge L0 and L1's desires, we simply ask
	 * to exit on each and every L2 page fault. This is done by setting
	 * MASK=MATCH=0 and (see below) EB.PF=1.
	 * Note that below we don't need special code to set EB.PF beyond the
	 * "or"ing of the EB of vmcs01 and vmcs12, because when enable_ept,
	 * vmcs01's EB.PF is 0 so the "or" will take vmcs12's value, and when
	 * !enable_ept, EB.PF is 1, so the "or" will always be 1.
	 */
	vmcs_write32(PAGE_FAULT_ERROR_CODE_MASK,
		enable_ept ? vmcs12->page_fault_error_code_mask : 0);
	vmcs_write32(PAGE_FAULT_ERROR_CODE_MATCH,
		enable_ept ? vmcs12->page_fault_error_code_match : 0);

	/* All VMFUNCs are currently emulated through L0 vmexits.  */
	if (cpu_has_vmx_vmfunc())
		vmcs_write64(VM_FUNCTION_CONTROL, 0);

	if (cpu_has_vmx_apicv()) {
		vmcs_write64(EOI_EXIT_BITMAP0, vmcs12->eoi_exit_bitmap0);
		vmcs_write64(EOI_EXIT_BITMAP1, vmcs12->eoi_exit_bitmap1);
		vmcs_write64(EOI_EXIT_BITMAP2, vmcs12->eoi_exit_bitmap2);
		vmcs_write64(EOI_EXIT_BITMAP3, vmcs12->eoi_exit_bitmap3);
	}

	/*
	 * Set host-state according to L0's settings (vmcs12 is irrelevant here)
	 * Some constant fields are set here by vmx_set_constant_host_state().
	 * Other fields are different per CPU, and will be set later when
	 * vmx_vcpu_load() is called, and when vmx_prepare_switch_to_guest()
	 * is called.
	 */
	vmx_set_constant_host_state(vmx);

	/*
	 * Set the MSR load/store lists to match L0's settings.
	 */
	vmcs_write32(VM_EXIT_MSR_STORE_COUNT, 0);
	vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_autoload.host.nr);
	vmcs_write64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.host.val));
	vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_autoload.guest.nr);
	vmcs_write64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.guest.val));

	set_cr4_guest_host_mask(vmx);

	if (kvm_mpx_supported()) {
		if (vmx->nested.nested_run_pending &&
			(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
			vmcs_write64(GUEST_BNDCFGS, vmcs12->guest_bndcfgs);
		else
			vmcs_write64(GUEST_BNDCFGS, vmx->nested.vmcs01_guest_bndcfgs);
	}

	if (enable_vpid) {
		if (nested_cpu_has_vpid(vmcs12) && vmx->nested.vpid02)
			vmcs_write16(VIRTUAL_PROCESSOR_ID, vmx->nested.vpid02);
		else
			vmcs_write16(VIRTUAL_PROCESSOR_ID, vmx->vpid);
	}

	/*
	 * L1 may access the L2's PDPTR, so save them to construct vmcs12
	 */
	if (enable_ept) {
		vmcs_write64(GUEST_PDPTR0, vmcs12->guest_pdptr0);
		vmcs_write64(GUEST_PDPTR1, vmcs12->guest_pdptr1);
		vmcs_write64(GUEST_PDPTR2, vmcs12->guest_pdptr2);
		vmcs_write64(GUEST_PDPTR3, vmcs12->guest_pdptr3);
	}

	if (cpu_has_vmx_msr_bitmap())
		vmcs_write64(MSR_BITMAP, __pa(vmx->nested.vmcs02.msr_bitmap));
}