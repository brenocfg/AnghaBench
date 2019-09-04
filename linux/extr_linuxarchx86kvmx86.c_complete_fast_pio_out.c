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
struct TYPE_3__ {int /*<<< orphan*/  linear_rip; scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ pio; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_is_linear_rip (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int complete_fast_pio_out(struct kvm_vcpu *vcpu)
{
	vcpu->arch.pio.count = 0;

	if (unlikely(!kvm_is_linear_rip(vcpu, vcpu->arch.pio.linear_rip)))
		return 1;

	return kvm_skip_emulated_instruction(vcpu);
}