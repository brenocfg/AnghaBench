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
struct kvm_lapic {int sw_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 TYPE_1__ apic_sw_disabled ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool kvm_apic_sw_enabled(struct kvm_lapic *apic)
{
	if (static_key_false(&apic_sw_disabled.key))
		return apic->sw_enabled;
	return true;
}