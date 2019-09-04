#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bad_page_dma; int /*<<< orphan*/ * bad_page_cpu; int /*<<< orphan*/  dev; } ;
struct etnaviv_iommuv1_domain {TYPE_1__ base; void* pgtable_cpu; int /*<<< orphan*/  pgtable_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PT_ENTRIES ; 
 int PT_SIZE ; 
 int SZ_4K ; 
 void* dma_alloc_wc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset32 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __etnaviv_iommu_init(struct etnaviv_iommuv1_domain *etnaviv_domain)
{
	u32 *p;
	int i;

	etnaviv_domain->base.bad_page_cpu =
			dma_alloc_wc(etnaviv_domain->base.dev, SZ_4K,
				     &etnaviv_domain->base.bad_page_dma,
				     GFP_KERNEL);
	if (!etnaviv_domain->base.bad_page_cpu)
		return -ENOMEM;

	p = etnaviv_domain->base.bad_page_cpu;
	for (i = 0; i < SZ_4K / 4; i++)
		*p++ = 0xdead55aa;

	etnaviv_domain->pgtable_cpu = dma_alloc_wc(etnaviv_domain->base.dev,
						   PT_SIZE,
						   &etnaviv_domain->pgtable_dma,
						   GFP_KERNEL);
	if (!etnaviv_domain->pgtable_cpu) {
		dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
			    etnaviv_domain->base.bad_page_cpu,
			    etnaviv_domain->base.bad_page_dma);
		return -ENOMEM;
	}

	memset32(etnaviv_domain->pgtable_cpu, etnaviv_domain->base.bad_page_dma,
		 PT_ENTRIES);

	return 0;
}