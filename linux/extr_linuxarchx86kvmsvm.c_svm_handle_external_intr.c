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
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static void svm_handle_external_intr(struct kvm_vcpu *vcpu)
{
	local_irq_enable();
	/*
	 * We must have an instruction with interrupts enabled, so
	 * the timer interrupt isn't delayed by the interrupt shadow.
	 */
	asm("nop");
	local_irq_disable();
}