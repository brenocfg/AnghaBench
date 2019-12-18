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
struct ipmmu_vmsa_domain {int /*<<< orphan*/  iop; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_io_pgtable_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  ipmmu_domain_destroy_context (struct ipmmu_vmsa_domain*) ; 
 int /*<<< orphan*/  kfree (struct ipmmu_vmsa_domain*) ; 
 struct ipmmu_vmsa_domain* to_vmsa_domain (struct iommu_domain*) ; 

__attribute__((used)) static void ipmmu_domain_free(struct iommu_domain *io_domain)
{
	struct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	/*
	 * Free the domain resources. We assume that all devices have already
	 * been detached.
	 */
	iommu_put_dma_cookie(io_domain);
	ipmmu_domain_destroy_context(domain);
	free_io_pgtable_ops(domain->iop);
	kfree(domain);
}