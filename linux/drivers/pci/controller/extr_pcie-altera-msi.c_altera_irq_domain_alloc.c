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
struct irq_domain {struct altera_msi* host_data; } ;
struct altera_msi {unsigned long num_of_vectors; int /*<<< orphan*/  lock; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MSI_INTMASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  altera_msi_bottom_irq_chip ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct altera_msi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int msi_readl (struct altera_msi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_writel (struct altera_msi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				   unsigned int nr_irqs, void *args)
{
	struct altera_msi *msi = domain->host_data;
	unsigned long bit;
	u32 mask;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&msi->lock);

	bit = find_first_zero_bit(msi->used, msi->num_of_vectors);
	if (bit >= msi->num_of_vectors) {
		mutex_unlock(&msi->lock);
		return -ENOSPC;
	}

	set_bit(bit, msi->used);

	mutex_unlock(&msi->lock);

	irq_domain_set_info(domain, virq, bit, &altera_msi_bottom_irq_chip,
			    domain->host_data, handle_simple_irq,
			    NULL, NULL);

	mask = msi_readl(msi, MSI_INTMASK);
	mask |= 1 << bit;
	msi_writel(msi, mask, MSI_INTMASK);

	return 0;
}