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
struct etnaviv_iommu_domain {int size; int /*<<< orphan*/ * ops; int /*<<< orphan*/  base; int /*<<< orphan*/  dev; } ;
struct etnaviv_iommuv1_domain {struct etnaviv_iommu_domain base; } ;
struct etnaviv_gpu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPU_MEM_START ; 
 int PT_ENTRIES ; 
 int SZ_4K ; 
 int __etnaviv_iommu_init (struct etnaviv_iommuv1_domain*) ; 
 int /*<<< orphan*/  etnaviv_iommuv1_ops ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommuv1_domain*) ; 
 struct etnaviv_iommuv1_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

struct etnaviv_iommu_domain *
etnaviv_iommuv1_domain_alloc(struct etnaviv_gpu *gpu)
{
	struct etnaviv_iommuv1_domain *etnaviv_domain;
	struct etnaviv_iommu_domain *domain;
	int ret;

	etnaviv_domain = kzalloc(sizeof(*etnaviv_domain), GFP_KERNEL);
	if (!etnaviv_domain)
		return NULL;

	domain = &etnaviv_domain->base;

	domain->dev = gpu->dev;
	domain->base = GPU_MEM_START;
	domain->size = PT_ENTRIES * SZ_4K;
	domain->ops = &etnaviv_iommuv1_ops;

	ret = __etnaviv_iommu_init(etnaviv_domain);
	if (ret)
		goto out_free;

	return &etnaviv_domain->base;

out_free:
	kfree(etnaviv_domain);
	return NULL;
}