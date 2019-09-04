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
typedef  int u32 ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 scalar_t__ apic_x2apic_mode (struct kvm_lapic*) ; 
 scalar_t__ kvm_apic_broadcast (struct kvm_lapic*,int) ; 
 int kvm_x2apic_id (struct kvm_lapic*) ; 
 int kvm_xapic_id (struct kvm_lapic*) ; 

__attribute__((used)) static bool kvm_apic_match_physical_addr(struct kvm_lapic *apic, u32 mda)
{
	if (kvm_apic_broadcast(apic, mda))
		return true;

	if (apic_x2apic_mode(apic))
		return mda == kvm_x2apic_id(apic);

	/*
	 * Hotplug hack: Make LAPIC in xAPIC mode also accept interrupts as if
	 * it were in x2APIC mode.  Hotplugged VCPUs start in xAPIC mode and
	 * this allows unique addressing of VCPUs with APIC ID over 0xff.
	 * The 0xff condition is needed because writeable xAPIC ID.
	 */
	if (kvm_x2apic_id(apic) > 0xff && mda == kvm_x2apic_id(apic))
		return true;

	return mda == kvm_xapic_id(apic);
}