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
struct kvm_vcpu {int pre_pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pi_post_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static void pi_post_block(struct kvm_vcpu *vcpu)
{
	if (vcpu->pre_pcpu == -1)
		return;

	WARN_ON(irqs_disabled());
	local_irq_disable();
	__pi_post_block(vcpu);
	local_irq_enable();
}