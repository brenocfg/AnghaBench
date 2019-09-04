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
struct s390_domain {int /*<<< orphan*/  dma_table; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cleanup_tables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s390_domain*) ; 
 struct s390_domain* to_s390_domain (struct iommu_domain*) ; 

__attribute__((used)) static void s390_domain_free(struct iommu_domain *domain)
{
	struct s390_domain *s390_domain = to_s390_domain(domain);

	dma_cleanup_tables(s390_domain->dma_table);
	kfree(s390_domain);
}