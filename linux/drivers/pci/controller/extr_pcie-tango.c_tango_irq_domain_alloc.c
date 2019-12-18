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
struct tango_pcie {int /*<<< orphan*/  used_msi_lock; int /*<<< orphan*/  used_msi; } ;
struct irq_domain {struct tango_pcie* host_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int MSI_MAX ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct tango_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tango_chip ; 

__attribute__((used)) static int tango_irq_domain_alloc(struct irq_domain *dom, unsigned int virq,
				  unsigned int nr_irqs, void *args)
{
	struct tango_pcie *pcie = dom->host_data;
	unsigned long flags;
	int pos;

	spin_lock_irqsave(&pcie->used_msi_lock, flags);
	pos = find_first_zero_bit(pcie->used_msi, MSI_MAX);
	if (pos >= MSI_MAX) {
		spin_unlock_irqrestore(&pcie->used_msi_lock, flags);
		return -ENOSPC;
	}
	__set_bit(pos, pcie->used_msi);
	spin_unlock_irqrestore(&pcie->used_msi_lock, flags);
	irq_domain_set_info(dom, virq, pos, &tango_chip,
			pcie, handle_edge_irq, NULL, NULL);

	return 0;
}