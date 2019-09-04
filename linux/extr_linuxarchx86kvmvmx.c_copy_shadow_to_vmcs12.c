#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned long u16 ;
struct vmcs {int dummy; } ;
struct TYPE_3__ {struct vmcs* shadow_vmcs; } ;
struct vcpu_vmx {TYPE_2__* loaded_vmcs; int /*<<< orphan*/  vcpu; TYPE_1__ vmcs01; } ;
struct TYPE_4__ {struct vmcs* vmcs; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long const**) ; 
 int /*<<< orphan*/  __vmcs_readl (unsigned long) ; 
 int /*<<< orphan*/  get_vmcs12 (int /*<<< orphan*/ *) ; 
 int const max_shadow_read_only_fields ; 
 int const max_shadow_read_write_fields ; 
 int /*<<< orphan*/  nested_cpu_has_vmwrite_any_field (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned long const* shadow_read_only_fields ; 
 unsigned long const* shadow_read_write_fields ; 
 int /*<<< orphan*/  vmcs12_write_any (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_clear (struct vmcs*) ; 
 int /*<<< orphan*/  vmcs_load (struct vmcs*) ; 

__attribute__((used)) static void copy_shadow_to_vmcs12(struct vcpu_vmx *vmx)
{
	const u16 *fields[] = {
		shadow_read_write_fields,
		shadow_read_only_fields
	};
	const int max_fields[] = {
		max_shadow_read_write_fields,
		max_shadow_read_only_fields
	};
	int i, q;
	unsigned long field;
	u64 field_value;
	struct vmcs *shadow_vmcs = vmx->vmcs01.shadow_vmcs;

	preempt_disable();

	vmcs_load(shadow_vmcs);

	for (q = 0; q < ARRAY_SIZE(fields); q++) {
		for (i = 0; i < max_fields[q]; i++) {
			field = fields[q][i];
			field_value = __vmcs_readl(field);
			vmcs12_write_any(get_vmcs12(&vmx->vcpu), field, field_value);
		}
		/*
		 * Skip the VM-exit information fields if they are read-only.
		 */
		if (!nested_cpu_has_vmwrite_any_field(&vmx->vcpu))
			break;
	}

	vmcs_clear(shadow_vmcs);
	vmcs_load(vmx->loaded_vmcs->vmcs);

	preempt_enable();
}