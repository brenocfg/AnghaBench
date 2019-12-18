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
struct xgene_msi {int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  num_cpus; int /*<<< orphan*/  bitmap; } ;
struct irq_domain {struct xgene_msi* host_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int NR_MSI_VEC ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct xgene_msi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_msi_bottom_irq_chip ; 

__attribute__((used)) static int xgene_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				  unsigned int nr_irqs, void *args)
{
	struct xgene_msi *msi = domain->host_data;
	int msi_irq;

	mutex_lock(&msi->bitmap_lock);

	msi_irq = bitmap_find_next_zero_area(msi->bitmap, NR_MSI_VEC, 0,
					     msi->num_cpus, 0);
	if (msi_irq < NR_MSI_VEC)
		bitmap_set(msi->bitmap, msi_irq, msi->num_cpus);
	else
		msi_irq = -ENOSPC;

	mutex_unlock(&msi->bitmap_lock);

	if (msi_irq < 0)
		return msi_irq;

	irq_domain_set_info(domain, virq, msi_irq,
			    &xgene_msi_bottom_irq_chip, domain->host_data,
			    handle_simple_irq, NULL, NULL);

	return 0;
}