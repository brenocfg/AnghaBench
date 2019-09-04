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
struct usnic_uiom_pd {int /*<<< orphan*/  devs; int /*<<< orphan*/  lock; void* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usnic_uiom_pd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_set_fault_handler (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usnic_uiom_pd*) ; 
 struct usnic_uiom_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_err (char*) ; 
 int /*<<< orphan*/  usnic_uiom_dma_fault ; 

struct usnic_uiom_pd *usnic_uiom_alloc_pd(void)
{
	struct usnic_uiom_pd *pd;
	void *domain;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	pd->domain = domain = iommu_domain_alloc(&pci_bus_type);
	if (!domain) {
		usnic_err("Failed to allocate IOMMU domain");
		kfree(pd);
		return ERR_PTR(-ENOMEM);
	}

	iommu_set_fault_handler(pd->domain, usnic_uiom_dma_fault, NULL);

	spin_lock_init(&pd->lock);
	INIT_LIST_HEAD(&pd->devs);

	return pd;
}