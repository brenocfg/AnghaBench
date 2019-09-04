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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

void kvm_mips_dump_stats(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
	int i, j;

	kvm_info("\nKVM VCPU[%d] COP0 Access Profile:\n", vcpu->vcpu_id);
	for (i = 0; i < N_MIPS_COPROC_REGS; i++) {
		for (j = 0; j < N_MIPS_COPROC_SEL; j++) {
			if (vcpu->arch.cop0->stat[i][j])
				kvm_info("%s[%d]: %lu\n", kvm_cop0_str[i], j,
					 vcpu->arch.cop0->stat[i][j]);
		}
	}
#endif
}