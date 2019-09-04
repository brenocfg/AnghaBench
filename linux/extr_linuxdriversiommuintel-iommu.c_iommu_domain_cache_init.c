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
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  iommu_domain_cache ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static inline int iommu_domain_cache_init(void)
{
	int ret = 0;

	iommu_domain_cache = kmem_cache_create("iommu_domain",
					 sizeof(struct dmar_domain),
					 0,
					 SLAB_HWCACHE_ALIGN,

					 NULL);
	if (!iommu_domain_cache) {
		pr_err("Couldn't create iommu_domain cache\n");
		ret = -ENOMEM;
	}

	return ret;
}