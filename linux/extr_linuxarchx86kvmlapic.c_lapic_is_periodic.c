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
 int apic_lvtt_period (struct kvm_lapic*) ; 

__attribute__((used)) static bool lapic_is_periodic(struct kvm_lapic *apic)
{
	return apic_lvtt_period(apic);
}