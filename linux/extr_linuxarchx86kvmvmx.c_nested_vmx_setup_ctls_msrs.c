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
typedef  int u64 ;
struct nested_vmx_msrs {int pinbased_ctls_low; int pinbased_ctls_high; int exit_ctls_low; int exit_ctls_high; int entry_ctls_low; int entry_ctls_high; int procbased_ctls_low; int procbased_ctls_high; int secondary_ctls_low; int secondary_ctls_high; int ept_caps; int vpid_caps; int misc_low; int misc_high; int basic; int cr0_fixed0; int vmcs_enum; int /*<<< orphan*/  cr4_fixed1; int /*<<< orphan*/  cr0_fixed1; int /*<<< orphan*/  cr4_fixed0; int /*<<< orphan*/  vmfunc_controls; } ;
struct TYPE_2__ {int ept; } ;

/* Variables and functions */
 int CPU_BASED_ACTIVATE_SECONDARY_CONTROLS ; 
 int CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int CPU_BASED_CR3_LOAD_EXITING ; 
 int CPU_BASED_CR3_STORE_EXITING ; 
 int CPU_BASED_HLT_EXITING ; 
 int CPU_BASED_INVLPG_EXITING ; 
 int CPU_BASED_MONITOR_EXITING ; 
 int CPU_BASED_MONITOR_TRAP_FLAG ; 
 int CPU_BASED_MOV_DR_EXITING ; 
 int CPU_BASED_MWAIT_EXITING ; 
 int CPU_BASED_PAUSE_EXITING ; 
 int CPU_BASED_RDPMC_EXITING ; 
 int CPU_BASED_RDTSC_EXITING ; 
 int CPU_BASED_TPR_SHADOW ; 
 int CPU_BASED_UNCOND_IO_EXITING ; 
 int CPU_BASED_USE_IO_BITMAPS ; 
 int CPU_BASED_USE_MSR_BITMAPS ; 
 int CPU_BASED_USE_TSC_OFFSETING ; 
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int CPU_BASED_VIRTUAL_NMI_PENDING ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR0_FIXED1 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR4_FIXED1 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_ENTRY_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_EXIT_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_MISC ; 
 int MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_PINBASED_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_PROCBASED_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_PROCBASED_CTLS2 ; 
 int PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int PIN_BASED_EXT_INTR_MASK ; 
 int PIN_BASED_NMI_EXITING ; 
 int PIN_BASED_POSTED_INTR ; 
 int PIN_BASED_VIRTUAL_NMIS ; 
 int PIN_BASED_VMX_PREEMPTION_TIMER ; 
 int SECONDARY_EXEC_APIC_REGISTER_VIRT ; 
 int SECONDARY_EXEC_DESC ; 
 int SECONDARY_EXEC_ENABLE_EPT ; 
 int SECONDARY_EXEC_ENABLE_PML ; 
 int SECONDARY_EXEC_ENABLE_VMFUNC ; 
 int SECONDARY_EXEC_ENABLE_VPID ; 
 int SECONDARY_EXEC_SHADOW_VMCS ; 
 int SECONDARY_EXEC_UNRESTRICTED_GUEST ; 
 int SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE ; 
 int SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY ; 
 int SECONDARY_EXEC_WBINVD_EXITING ; 
 int VMCS12_MAX_FIELD_INDEX ; 
 int VMCS12_REVISION ; 
 scalar_t__ VMCS12_SIZE ; 
 int VMX_BASIC_INOUT ; 
 int VMX_BASIC_MEM_TYPE_SHIFT ; 
 int VMX_BASIC_MEM_TYPE_WB ; 
 int VMX_BASIC_TRUE_CTLS ; 
 int VMX_BASIC_VMCS_SIZE_SHIFT ; 
 int VMX_EPTP_WB_BIT ; 
 int VMX_EPT_1GB_PAGE_BIT ; 
 int VMX_EPT_2MB_PAGE_BIT ; 
 int VMX_EPT_AD_BIT ; 
 int VMX_EPT_EXECUTE_ONLY_BIT ; 
 int VMX_EPT_EXTENT_CONTEXT_BIT ; 
 int VMX_EPT_EXTENT_GLOBAL_BIT ; 
 int VMX_EPT_INVEPT_BIT ; 
 int VMX_EPT_PAGE_WALK_4_BIT ; 
 int VMX_MISC_ACTIVITY_HLT ; 
 int VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE ; 
 int VMX_MISC_SAVE_EFER_LMA ; 
 int /*<<< orphan*/  VMX_VMFUNC_EPTP_SWITCHING ; 
 int VMX_VPID_EXTENT_SUPPORTED_MASK ; 
 int VMX_VPID_INVVPID_BIT ; 
 int VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int VM_ENTRY_LOAD_DEBUG_CONTROLS ; 
 int VM_ENTRY_LOAD_IA32_EFER ; 
 int VM_ENTRY_LOAD_IA32_PAT ; 
 int VM_EXIT_ACK_INTR_ON_EXIT ; 
 int VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR ; 
 int VM_EXIT_LOAD_IA32_EFER ; 
 int VM_EXIT_LOAD_IA32_PAT ; 
 int VM_EXIT_SAVE_DEBUG_CONTROLS ; 
 int VM_EXIT_SAVE_IA32_EFER ; 
 int VM_EXIT_SAVE_IA32_PAT ; 
 int VM_EXIT_SAVE_VMX_PREEMPTION_TIMER ; 
 int X86_CR0_NE ; 
 int X86_CR0_PE ; 
 int X86_CR0_PG ; 
 int /*<<< orphan*/  X86_CR4_VMXE ; 
 scalar_t__ cpu_has_vmx_basic_inout () ; 
 scalar_t__ cpu_has_vmx_ept_execute_only () ; 
 scalar_t__ cpu_has_vmx_vmfunc () ; 
 scalar_t__ enable_ept ; 
 scalar_t__ enable_ept_ad_bits ; 
 scalar_t__ enable_unrestricted_guest ; 
 scalar_t__ enable_vpid ; 
 scalar_t__ flexpriority_enabled ; 
 int /*<<< orphan*/  memset (struct nested_vmx_msrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nested ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmx_capability ; 

__attribute__((used)) static void nested_vmx_setup_ctls_msrs(struct nested_vmx_msrs *msrs, bool apicv)
{
	if (!nested) {
		memset(msrs, 0, sizeof(*msrs));
		return;
	}

	/*
	 * Note that as a general rule, the high half of the MSRs (bits in
	 * the control fields which may be 1) should be initialized by the
	 * intersection of the underlying hardware's MSR (i.e., features which
	 * can be supported) and the list of features we want to expose -
	 * because they are known to be properly supported in our code.
	 * Also, usually, the low half of the MSRs (bits which must be 1) can
	 * be set to 0, meaning that L1 may turn off any of these bits. The
	 * reason is that if one of these bits is necessary, it will appear
	 * in vmcs01 and prepare_vmcs02, when it bitwise-or's the control
	 * fields of vmcs01 and vmcs02, will turn these bits off - and
	 * nested_vmx_exit_reflected() will not pass related exits to L1.
	 * These rules have exceptions below.
	 */

	/* pin-based controls */
	rdmsr(MSR_IA32_VMX_PINBASED_CTLS,
		msrs->pinbased_ctls_low,
		msrs->pinbased_ctls_high);
	msrs->pinbased_ctls_low |=
		PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->pinbased_ctls_high &=
		PIN_BASED_EXT_INTR_MASK |
		PIN_BASED_NMI_EXITING |
		PIN_BASED_VIRTUAL_NMIS |
		(apicv ? PIN_BASED_POSTED_INTR : 0);
	msrs->pinbased_ctls_high |=
		PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR |
		PIN_BASED_VMX_PREEMPTION_TIMER;

	/* exit controls */
	rdmsr(MSR_IA32_VMX_EXIT_CTLS,
		msrs->exit_ctls_low,
		msrs->exit_ctls_high);
	msrs->exit_ctls_low =
		VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR;

	msrs->exit_ctls_high &=
#ifdef CONFIG_X86_64
		VM_EXIT_HOST_ADDR_SPACE_SIZE |
#endif
		VM_EXIT_LOAD_IA32_PAT | VM_EXIT_SAVE_IA32_PAT;
	msrs->exit_ctls_high |=
		VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR |
		VM_EXIT_LOAD_IA32_EFER | VM_EXIT_SAVE_IA32_EFER |
		VM_EXIT_SAVE_VMX_PREEMPTION_TIMER | VM_EXIT_ACK_INTR_ON_EXIT;

	/* We support free control of debug control saving. */
	msrs->exit_ctls_low &= ~VM_EXIT_SAVE_DEBUG_CONTROLS;

	/* entry controls */
	rdmsr(MSR_IA32_VMX_ENTRY_CTLS,
		msrs->entry_ctls_low,
		msrs->entry_ctls_high);
	msrs->entry_ctls_low =
		VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->entry_ctls_high &=
#ifdef CONFIG_X86_64
		VM_ENTRY_IA32E_MODE |
#endif
		VM_ENTRY_LOAD_IA32_PAT;
	msrs->entry_ctls_high |=
		(VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR | VM_ENTRY_LOAD_IA32_EFER);

	/* We support free control of debug control loading. */
	msrs->entry_ctls_low &= ~VM_ENTRY_LOAD_DEBUG_CONTROLS;

	/* cpu-based controls */
	rdmsr(MSR_IA32_VMX_PROCBASED_CTLS,
		msrs->procbased_ctls_low,
		msrs->procbased_ctls_high);
	msrs->procbased_ctls_low =
		CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->procbased_ctls_high &=
		CPU_BASED_VIRTUAL_INTR_PENDING |
		CPU_BASED_VIRTUAL_NMI_PENDING | CPU_BASED_USE_TSC_OFFSETING |
		CPU_BASED_HLT_EXITING | CPU_BASED_INVLPG_EXITING |
		CPU_BASED_MWAIT_EXITING | CPU_BASED_CR3_LOAD_EXITING |
		CPU_BASED_CR3_STORE_EXITING |
#ifdef CONFIG_X86_64
		CPU_BASED_CR8_LOAD_EXITING | CPU_BASED_CR8_STORE_EXITING |
#endif
		CPU_BASED_MOV_DR_EXITING | CPU_BASED_UNCOND_IO_EXITING |
		CPU_BASED_USE_IO_BITMAPS | CPU_BASED_MONITOR_TRAP_FLAG |
		CPU_BASED_MONITOR_EXITING | CPU_BASED_RDPMC_EXITING |
		CPU_BASED_RDTSC_EXITING | CPU_BASED_PAUSE_EXITING |
		CPU_BASED_TPR_SHADOW | CPU_BASED_ACTIVATE_SECONDARY_CONTROLS;
	/*
	 * We can allow some features even when not supported by the
	 * hardware. For example, L1 can specify an MSR bitmap - and we
	 * can use it to avoid exits to L1 - even when L0 runs L2
	 * without MSR bitmaps.
	 */
	msrs->procbased_ctls_high |=
		CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR |
		CPU_BASED_USE_MSR_BITMAPS;

	/* We support free control of CR3 access interception. */
	msrs->procbased_ctls_low &=
		~(CPU_BASED_CR3_LOAD_EXITING | CPU_BASED_CR3_STORE_EXITING);

	/*
	 * secondary cpu-based controls.  Do not include those that
	 * depend on CPUID bits, they are added later by vmx_cpuid_update.
	 */
	if (msrs->procbased_ctls_high & CPU_BASED_ACTIVATE_SECONDARY_CONTROLS)
		rdmsr(MSR_IA32_VMX_PROCBASED_CTLS2,
		      msrs->secondary_ctls_low,
		      msrs->secondary_ctls_high);

	msrs->secondary_ctls_low = 0;
	msrs->secondary_ctls_high &=
		SECONDARY_EXEC_DESC |
		SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE |
		SECONDARY_EXEC_APIC_REGISTER_VIRT |
		SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |
		SECONDARY_EXEC_WBINVD_EXITING;

	/*
	 * We can emulate "VMCS shadowing," even if the hardware
	 * doesn't support it.
	 */
	msrs->secondary_ctls_high |=
		SECONDARY_EXEC_SHADOW_VMCS;

	if (enable_ept) {
		/* nested EPT: emulate EPT also to L1 */
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_EPT;
		msrs->ept_caps = VMX_EPT_PAGE_WALK_4_BIT |
			 VMX_EPTP_WB_BIT | VMX_EPT_INVEPT_BIT;
		if (cpu_has_vmx_ept_execute_only())
			msrs->ept_caps |=
				VMX_EPT_EXECUTE_ONLY_BIT;
		msrs->ept_caps &= vmx_capability.ept;
		msrs->ept_caps |= VMX_EPT_EXTENT_GLOBAL_BIT |
			VMX_EPT_EXTENT_CONTEXT_BIT | VMX_EPT_2MB_PAGE_BIT |
			VMX_EPT_1GB_PAGE_BIT;
		if (enable_ept_ad_bits) {
			msrs->secondary_ctls_high |=
				SECONDARY_EXEC_ENABLE_PML;
			msrs->ept_caps |= VMX_EPT_AD_BIT;
		}
	}

	if (cpu_has_vmx_vmfunc()) {
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_VMFUNC;
		/*
		 * Advertise EPTP switching unconditionally
		 * since we emulate it
		 */
		if (enable_ept)
			msrs->vmfunc_controls =
				VMX_VMFUNC_EPTP_SWITCHING;
	}

	/*
	 * Old versions of KVM use the single-context version without
	 * checking for support, so declare that it is supported even
	 * though it is treated as global context.  The alternative is
	 * not failing the single-context invvpid, and it is worse.
	 */
	if (enable_vpid) {
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_VPID;
		msrs->vpid_caps = VMX_VPID_INVVPID_BIT |
			VMX_VPID_EXTENT_SUPPORTED_MASK;
	}

	if (enable_unrestricted_guest)
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_UNRESTRICTED_GUEST;

	if (flexpriority_enabled)
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;

	/* miscellaneous data */
	rdmsr(MSR_IA32_VMX_MISC,
		msrs->misc_low,
		msrs->misc_high);
	msrs->misc_low &= VMX_MISC_SAVE_EFER_LMA;
	msrs->misc_low |=
		MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS |
		VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE |
		VMX_MISC_ACTIVITY_HLT;
	msrs->misc_high = 0;

	/*
	 * This MSR reports some information about VMX support. We
	 * should return information about the VMX we emulate for the
	 * guest, and the VMCS structure we give it - not about the
	 * VMX support of the underlying hardware.
	 */
	msrs->basic =
		VMCS12_REVISION |
		VMX_BASIC_TRUE_CTLS |
		((u64)VMCS12_SIZE << VMX_BASIC_VMCS_SIZE_SHIFT) |
		(VMX_BASIC_MEM_TYPE_WB << VMX_BASIC_MEM_TYPE_SHIFT);

	if (cpu_has_vmx_basic_inout())
		msrs->basic |= VMX_BASIC_INOUT;

	/*
	 * These MSRs specify bits which the guest must keep fixed on
	 * while L1 is in VMXON mode (in L1's root mode, or running an L2).
	 * We picked the standard core2 setting.
	 */
#define VMXON_CR0_ALWAYSON     (X86_CR0_PE | X86_CR0_PG | X86_CR0_NE)
#define VMXON_CR4_ALWAYSON     X86_CR4_VMXE
	msrs->cr0_fixed0 = VMXON_CR0_ALWAYSON;
	msrs->cr4_fixed0 = VMXON_CR4_ALWAYSON;

	/* These MSRs specify bits which the guest must keep fixed off. */
	rdmsrl(MSR_IA32_VMX_CR0_FIXED1, msrs->cr0_fixed1);
	rdmsrl(MSR_IA32_VMX_CR4_FIXED1, msrs->cr4_fixed1);

	/* highest index: VMX_PREEMPTION_TIMER_VALUE */
	msrs->vmcs_enum = VMCS12_MAX_FIELD_INDEX << 1;
}