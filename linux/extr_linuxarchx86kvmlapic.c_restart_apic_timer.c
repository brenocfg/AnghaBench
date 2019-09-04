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
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  start_hv_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  start_sw_timer (struct kvm_lapic*) ; 

__attribute__((used)) static void restart_apic_timer(struct kvm_lapic *apic)
{
	preempt_disable();
	if (!start_hv_timer(apic))
		start_sw_timer(apic);
	preempt_enable();
}