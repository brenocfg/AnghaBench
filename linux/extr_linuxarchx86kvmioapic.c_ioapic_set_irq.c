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
struct TYPE_2__ {scalar_t__ trig_mode; } ;
union kvm_ioapic_redirect_entry {int /*<<< orphan*/  bits; TYPE_1__ fields; } ;
typedef  int u32 ;
struct kvm_ioapic {int irr; int irr_delivered; union kvm_ioapic_redirect_entry* redirtbl; } ;

/* Variables and functions */
 scalar_t__ IOAPIC_EDGE_TRIG ; 
 unsigned int RTC_GSI ; 
 int ioapic_service (struct kvm_ioapic*,unsigned int,int) ; 
 scalar_t__ rtc_irq_check_coalesced (struct kvm_ioapic*) ; 
 int /*<<< orphan*/  trace_kvm_ioapic_set_irq (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int ioapic_set_irq(struct kvm_ioapic *ioapic, unsigned int irq,
		int irq_level, bool line_status)
{
	union kvm_ioapic_redirect_entry entry;
	u32 mask = 1 << irq;
	u32 old_irr;
	int edge, ret;

	entry = ioapic->redirtbl[irq];
	edge = (entry.fields.trig_mode == IOAPIC_EDGE_TRIG);

	if (!irq_level) {
		ioapic->irr &= ~mask;
		ret = 1;
		goto out;
	}

	/*
	 * Return 0 for coalesced interrupts; for edge-triggered interrupts,
	 * this only happens if a previous edge has not been delivered due
	 * do masking.  For level interrupts, the remote_irr field tells
	 * us if the interrupt is waiting for an EOI.
	 *
	 * RTC is special: it is edge-triggered, but userspace likes to know
	 * if it has been already ack-ed via EOI because coalesced RTC
	 * interrupts lead to time drift in Windows guests.  So we track
	 * EOI manually for the RTC interrupt.
	 */
	if (irq == RTC_GSI && line_status &&
		rtc_irq_check_coalesced(ioapic)) {
		ret = 0;
		goto out;
	}

	old_irr = ioapic->irr;
	ioapic->irr |= mask;
	if (edge) {
		ioapic->irr_delivered &= ~mask;
		if (old_irr == ioapic->irr) {
			ret = 0;
			goto out;
		}
	}

	ret = ioapic_service(ioapic, irq, line_status);

out:
	trace_kvm_ioapic_set_irq(entry.bits, irq, ret == 0);
	return ret;
}