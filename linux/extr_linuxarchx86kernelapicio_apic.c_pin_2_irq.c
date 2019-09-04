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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int dstirq; } ;

/* Variables and functions */
 TYPE_1__* mp_irqs ; 
 int mp_map_pin_to_irq (int /*<<< orphan*/ ,int,int,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_pin_to_gsi (int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pin_2_irq(int idx, int ioapic, int pin, unsigned int flags)
{
	u32 gsi = mp_pin_to_gsi(ioapic, pin);

	/*
	 * Debugging check, we are in big trouble if this message pops up!
	 */
	if (mp_irqs[idx].dstirq != pin)
		pr_err("broken BIOS or MPTABLE parser, ayiee!!\n");

#ifdef CONFIG_X86_32
	/*
	 * PCI IRQ command line redirection. Yes, limits are hardcoded.
	 */
	if ((pin >= 16) && (pin <= 23)) {
		if (pirq_entries[pin-16] != -1) {
			if (!pirq_entries[pin-16]) {
				apic_printk(APIC_VERBOSE, KERN_DEBUG
						"disabling PIRQ%d\n", pin-16);
			} else {
				int irq = pirq_entries[pin-16];
				apic_printk(APIC_VERBOSE, KERN_DEBUG
						"using PIRQ%d -> IRQ %d\n",
						pin-16, irq);
				return irq;
			}
		}
	}
#endif

	return  mp_map_pin_to_irq(gsi, idx, ioapic, pin, flags, NULL);
}