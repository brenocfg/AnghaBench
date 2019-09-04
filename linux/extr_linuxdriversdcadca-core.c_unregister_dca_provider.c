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
struct pci_bus {int dummy; } ;
struct device {int dummy; } ;
struct dca_provider {int /*<<< orphan*/  node; } ;
struct dca_domain {int /*<<< orphan*/  dca_providers; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_PROVIDER_REMOVE ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dca_domains ; 
 struct dca_domain* dca_find_domain (struct pci_bus*) ; 
 int /*<<< orphan*/  dca_free_domain (struct dca_domain*) ; 
 int /*<<< orphan*/  dca_lock ; 
 struct pci_bus* dca_pci_rc_from_dev (struct device*) ; 
 int /*<<< orphan*/  dca_provider_chain ; 
 int /*<<< orphan*/  dca_sysfs_remove_provider (struct dca_provider*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void unregister_dca_provider(struct dca_provider *dca, struct device *dev)
{
	unsigned long flags;
	struct pci_bus *pci_rc;
	struct dca_domain *domain;

	blocking_notifier_call_chain(&dca_provider_chain,
				     DCA_PROVIDER_REMOVE, NULL);

	raw_spin_lock_irqsave(&dca_lock, flags);

	if (list_empty(&dca_domains)) {
		raw_spin_unlock_irqrestore(&dca_lock, flags);
		return;
	}

	list_del(&dca->node);

	pci_rc = dca_pci_rc_from_dev(dev);
	domain = dca_find_domain(pci_rc);
	if (list_empty(&domain->dca_providers))
		dca_free_domain(domain);

	raw_spin_unlock_irqrestore(&dca_lock, flags);

	dca_sysfs_remove_provider(dca);
}