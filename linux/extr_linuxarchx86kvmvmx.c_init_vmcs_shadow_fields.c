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
typedef  scalar_t__ u16 ;

/* Variables and functions */
#define  GUEST_INTR_STATUS 130 
#define  GUEST_PML_INDEX 129 
 scalar_t__ VMCS_FIELD_WIDTH_U64 ; 
#define  VMX_PREEMPTION_TIMER_VALUE 128 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_vmx_apicv () ; 
 int /*<<< orphan*/  cpu_has_vmx_pml () ; 
 int /*<<< orphan*/  cpu_has_vmx_preemption_timer () ; 
 int max_shadow_read_only_fields ; 
 int max_shadow_read_write_fields ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 scalar_t__* shadow_read_only_fields ; 
 scalar_t__* shadow_read_write_fields ; 
 scalar_t__ vmcs_field_width (scalar_t__) ; 
 int /*<<< orphan*/  vmx_vmread_bitmap ; 
 int /*<<< orphan*/  vmx_vmwrite_bitmap ; 

__attribute__((used)) static void init_vmcs_shadow_fields(void)
{
	int i, j;

	for (i = j = 0; i < max_shadow_read_only_fields; i++) {
		u16 field = shadow_read_only_fields[i];
		if (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shadow_read_only_fields ||
		     shadow_read_only_fields[i + 1] != field + 1))
			pr_err("Missing field from shadow_read_only_field %x\n",
			       field + 1);

		clear_bit(field, vmx_vmread_bitmap);
#ifdef CONFIG_X86_64
		if (field & 1)
			continue;
#endif
		if (j < i)
			shadow_read_only_fields[j] = field;
		j++;
	}
	max_shadow_read_only_fields = j;

	for (i = j = 0; i < max_shadow_read_write_fields; i++) {
		u16 field = shadow_read_write_fields[i];
		if (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shadow_read_write_fields ||
		     shadow_read_write_fields[i + 1] != field + 1))
			pr_err("Missing field from shadow_read_write_field %x\n",
			       field + 1);

		/*
		 * PML and the preemption timer can be emulated, but the
		 * processor cannot vmwrite to fields that don't exist
		 * on bare metal.
		 */
		switch (field) {
		case GUEST_PML_INDEX:
			if (!cpu_has_vmx_pml())
				continue;
			break;
		case VMX_PREEMPTION_TIMER_VALUE:
			if (!cpu_has_vmx_preemption_timer())
				continue;
			break;
		case GUEST_INTR_STATUS:
			if (!cpu_has_vmx_apicv())
				continue;
			break;
		default:
			break;
		}

		clear_bit(field, vmx_vmwrite_bitmap);
		clear_bit(field, vmx_vmread_bitmap);
#ifdef CONFIG_X86_64
		if (field & 1)
			continue;
#endif
		if (j < i)
			shadow_read_write_fields[j] = field;
		j++;
	}
	max_shadow_read_write_fields = j;
}