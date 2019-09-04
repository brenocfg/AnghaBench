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
struct TYPE_2__ {unsigned long* regs; int /*<<< orphan*/  regs_avail; int /*<<< orphan*/  regs_dirty; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum kvm_reg { ____Placeholder_kvm_reg } kvm_reg ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 

__attribute__((used)) static inline void kvm_register_write(struct kvm_vcpu *vcpu,
				      enum kvm_reg reg,
				      unsigned long val)
{
	vcpu->arch.regs[reg] = val;
	__set_bit(reg, (unsigned long *)&vcpu->arch.regs_dirty);
	__set_bit(reg, (unsigned long *)&vcpu->arch.regs_avail);
}