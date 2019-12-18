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
struct page {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  gaw; scalar_t__ pgd; int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_MAX_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_pagelist (struct page*) ; 
 int /*<<< orphan*/  domain_remove_dev_info (struct dmar_domain*) ; 
 struct page* domain_unmap (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_domain_mem (struct dmar_domain*) ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void domain_exit(struct dmar_domain *domain)
{

	/* Remove associated devices and clear attached or cached domains */
	domain_remove_dev_info(domain);

	/* destroy iovas */
	put_iova_domain(&domain->iovad);

	if (domain->pgd) {
		struct page *freelist;

		freelist = domain_unmap(domain, 0, DOMAIN_MAX_PFN(domain->gaw));
		dma_free_pagelist(freelist);
	}

	free_domain_mem(domain);
}