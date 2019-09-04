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
struct irq_bucket {int /*<<< orphan*/  irq; struct irq_bucket* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBI2DEVID (unsigned int) ; 
 unsigned int acquire_sbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bw_clear_intr_mask (int,unsigned int) ; 
 int bw_get_intr_mask (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_bucket** irq_map ; 
 int /*<<< orphan*/  release_sbi (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sun4d_encode_irq (unsigned int,int,unsigned int) ; 

__attribute__((used)) static void sun4d_sbus_handler_irq(int sbusl)
{
	unsigned int bus_mask;
	unsigned int sbino, slot;
	unsigned int sbil;

	bus_mask = bw_get_intr_mask(sbusl) & 0x3ffff;
	bw_clear_intr_mask(sbusl, bus_mask);

	sbil = (sbusl << 2);
	/* Loop for each pending SBI */
	for (sbino = 0; bus_mask; sbino++, bus_mask >>= 1) {
		unsigned int idx, mask;

		if (!(bus_mask & 1))
			continue;
		/* XXX This seems to ACK the irq twice.  acquire_sbi()
		 * XXX uses swap, therefore this writes 0xf << sbil,
		 * XXX then later release_sbi() will write the individual
		 * XXX bits which were set again.
		 */
		mask = acquire_sbi(SBI2DEVID(sbino), 0xf << sbil);
		mask &= (0xf << sbil);

		/* Loop for each pending SBI slot */
		slot = (1 << sbil);
		for (idx = 0; mask != 0; idx++, slot <<= 1) {
			unsigned int pil;
			struct irq_bucket *p;

			if (!(mask & slot))
				continue;

			mask &= ~slot;
			pil = sun4d_encode_irq(sbino, sbusl, idx);

			p = irq_map[pil];
			while (p) {
				struct irq_bucket *next;

				next = p->next;
				generic_handle_irq(p->irq);
				p = next;
			}
			release_sbi(SBI2DEVID(sbino), slot);
		}
	}
}