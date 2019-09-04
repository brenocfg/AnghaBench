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
typedef  int u64 ;
struct etnaviv_iommu_domain {int size; int /*<<< orphan*/ * ops; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct etnaviv_iommuv2_domain {struct etnaviv_iommu_domain base; } ;
struct etnaviv_gpu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SZ_1G ; 
 int etnaviv_iommuv2_init (struct etnaviv_iommuv2_domain*) ; 
 int /*<<< orphan*/  etnaviv_iommuv2_ops ; 
 int /*<<< orphan*/  vfree (struct etnaviv_iommuv2_domain*) ; 
 struct etnaviv_iommuv2_domain* vzalloc (int) ; 

struct etnaviv_iommu_domain *
etnaviv_iommuv2_domain_alloc(struct etnaviv_gpu *gpu)
{
	struct etnaviv_iommuv2_domain *etnaviv_domain;
	struct etnaviv_iommu_domain *domain;
	int ret;

	etnaviv_domain = vzalloc(sizeof(*etnaviv_domain));
	if (!etnaviv_domain)
		return NULL;

	domain = &etnaviv_domain->base;

	domain->dev = gpu->dev;
	domain->base = 0;
	domain->size = (u64)SZ_1G * 4;
	domain->ops = &etnaviv_iommuv2_ops;

	ret = etnaviv_iommuv2_init(etnaviv_domain);
	if (ret)
		goto out_free;

	return &etnaviv_domain->base;

out_free:
	vfree(etnaviv_domain);
	return NULL;
}