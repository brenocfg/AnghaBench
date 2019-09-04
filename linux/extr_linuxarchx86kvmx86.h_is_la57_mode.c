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

__attribute__((used)) static inline bool is_la57_mode(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	return (vcpu->arch.efer & EFER_LMA) &&
		 kvm_read_cr4_bits(vcpu, X86_CR4_LA57);
#else
	return 0;
#endif
}