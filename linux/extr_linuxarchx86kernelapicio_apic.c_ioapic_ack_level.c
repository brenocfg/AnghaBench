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
struct irq_data {int /*<<< orphan*/  chip_data; } ;
struct irq_cfg {int vector; } ;

/* Variables and functions */
 scalar_t__ APIC_TMR ; 
 int /*<<< orphan*/  ack_APIC_irq () ; 
 unsigned long apic_read (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eoi_ioapic_pin (int,int /*<<< orphan*/ ) ; 
 int ioapic_irqd_mask (struct irq_data*) ; 
 int /*<<< orphan*/  ioapic_irqd_unmask (struct irq_data*,int) ; 
 int /*<<< orphan*/  irq_complete_move (struct irq_cfg*) ; 
 int /*<<< orphan*/  irq_mis_count ; 
 struct irq_cfg* irqd_cfg (struct irq_data*) ; 

__attribute__((used)) static void ioapic_ack_level(struct irq_data *irq_data)
{
	struct irq_cfg *cfg = irqd_cfg(irq_data);
	unsigned long v;
	bool masked;
	int i;

	irq_complete_move(cfg);
	masked = ioapic_irqd_mask(irq_data);

	/*
	 * It appears there is an erratum which affects at least version 0x11
	 * of I/O APIC (that's the 82093AA and cores integrated into various
	 * chipsets).  Under certain conditions a level-triggered interrupt is
	 * erroneously delivered as edge-triggered one but the respective IRR
	 * bit gets set nevertheless.  As a result the I/O unit expects an EOI
	 * message but it will never arrive and further interrupts are blocked
	 * from the source.  The exact reason is so far unknown, but the
	 * phenomenon was observed when two consecutive interrupt requests
	 * from a given source get delivered to the same CPU and the source is
	 * temporarily disabled in between.
	 *
	 * A workaround is to simulate an EOI message manually.  We achieve it
	 * by setting the trigger mode to edge and then to level when the edge
	 * trigger mode gets detected in the TMR of a local APIC for a
	 * level-triggered interrupt.  We mask the source for the time of the
	 * operation to prevent an edge-triggered interrupt escaping meanwhile.
	 * The idea is from Manfred Spraul.  --macro
	 *
	 * Also in the case when cpu goes offline, fixup_irqs() will forward
	 * any unhandled interrupt on the offlined cpu to the new cpu
	 * destination that is handling the corresponding interrupt. This
	 * interrupt forwarding is done via IPI's. Hence, in this case also
	 * level-triggered io-apic interrupt will be seen as an edge
	 * interrupt in the IRR. And we can't rely on the cpu's EOI
	 * to be broadcasted to the IO-APIC's which will clear the remoteIRR
	 * corresponding to the level-triggered interrupt. Hence on IO-APIC's
	 * supporting EOI register, we do an explicit EOI to clear the
	 * remote IRR and on IO-APIC's which don't have an EOI register,
	 * we use the above logic (mask+edge followed by unmask+level) from
	 * Manfred Spraul to clear the remote IRR.
	 */
	i = cfg->vector;
	v = apic_read(APIC_TMR + ((i & ~0x1f) >> 1));

	/*
	 * We must acknowledge the irq before we move it or the acknowledge will
	 * not propagate properly.
	 */
	ack_APIC_irq();

	/*
	 * Tail end of clearing remote IRR bit (either by delivering the EOI
	 * message via io-apic EOI register write or simulating it using
	 * mask+edge followed by unnask+level logic) manually when the
	 * level triggered interrupt is seen as the edge triggered interrupt
	 * at the cpu.
	 */
	if (!(v & (1 << (i & 0x1f)))) {
		atomic_inc(&irq_mis_count);
		eoi_ioapic_pin(cfg->vector, irq_data->chip_data);
	}

	ioapic_irqd_unmask(irq_data, masked);
}