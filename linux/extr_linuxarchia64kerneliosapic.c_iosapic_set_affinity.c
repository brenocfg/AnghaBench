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
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
iosapic_set_affinity(struct irq_data *data, const struct cpumask *mask,
		     bool force)
{
#ifdef CONFIG_SMP
	unsigned int irq = data->irq;
	u32 high32, low32;
	int cpu, dest, rte_index;
	int redir = (irq & IA64_IRQ_REDIRECTED) ? 1 : 0;
	struct iosapic_rte_info *rte;
	struct iosapic *iosapic;

	irq &= (~IA64_IRQ_REDIRECTED);

	cpu = cpumask_first_and(cpu_online_mask, mask);
	if (cpu >= nr_cpu_ids)
		return -1;

	if (irq_prepare_move(irq, cpu))
		return -1;

	dest = cpu_physical_id(cpu);

	if (!iosapic_intr_info[irq].count)
		return -1;			/* not an IOSAPIC interrupt */

	set_irq_affinity_info(irq, dest, redir);

	/* dest contains both id and eid */
	high32 = dest << IOSAPIC_DEST_SHIFT;

	low32 = iosapic_intr_info[irq].low32 & ~(7 << IOSAPIC_DELIVERY_SHIFT);
	if (redir)
		/* change delivery mode to lowest priority */
		low32 |= (IOSAPIC_LOWEST_PRIORITY << IOSAPIC_DELIVERY_SHIFT);
	else
		/* change delivery mode to fixed */
		low32 |= (IOSAPIC_FIXED << IOSAPIC_DELIVERY_SHIFT);
	low32 &= IOSAPIC_VECTOR_MASK;
	low32 |= irq_to_vector(irq);

	iosapic_intr_info[irq].low32 = low32;
	iosapic_intr_info[irq].dest = dest;
	list_for_each_entry(rte, &iosapic_intr_info[irq].rtes, rte_list) {
		iosapic = rte->iosapic;
		rte_index = rte->rte_index;
		iosapic_write(iosapic, IOSAPIC_RTE_HIGH(rte_index), high32);
		iosapic_write(iosapic, IOSAPIC_RTE_LOW(rte_index), low32);
	}

#endif
	return 0;
}