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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bad_page_dma; void* bad_page_cpu; } ;
struct etnaviv_iommuv2_domain {int /*<<< orphan*/  mtlb_dma; void* mtlb_cpu; TYPE_1__ base; int /*<<< orphan*/  pta_dma; void* pta_cpu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMUv2_MAX_STLB_ENTRIES ; 
 int MMUv2_PTE_EXCEPTION ; 
 int SZ_4K ; 
 void* dma_alloc_wc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset32 (void*,int,int) ; 

__attribute__((used)) static int etnaviv_iommuv2_init(struct etnaviv_iommuv2_domain *etnaviv_domain)
{
	int ret;

	/* allocate scratch page */
	etnaviv_domain->base.bad_page_cpu =
			dma_alloc_wc(etnaviv_domain->base.dev, SZ_4K,
				     &etnaviv_domain->base.bad_page_dma,
				     GFP_KERNEL);
	if (!etnaviv_domain->base.bad_page_cpu) {
		ret = -ENOMEM;
		goto fail_mem;
	}

	memset32(etnaviv_domain->base.bad_page_cpu, 0xdead55aa,
		 SZ_4K / sizeof(u32));

	etnaviv_domain->pta_cpu = dma_alloc_wc(etnaviv_domain->base.dev,
					       SZ_4K, &etnaviv_domain->pta_dma,
					       GFP_KERNEL);
	if (!etnaviv_domain->pta_cpu) {
		ret = -ENOMEM;
		goto fail_mem;
	}

	etnaviv_domain->mtlb_cpu = dma_alloc_wc(etnaviv_domain->base.dev,
						SZ_4K, &etnaviv_domain->mtlb_dma,
						GFP_KERNEL);
	if (!etnaviv_domain->mtlb_cpu) {
		ret = -ENOMEM;
		goto fail_mem;
	}

	memset32(etnaviv_domain->mtlb_cpu, MMUv2_PTE_EXCEPTION,
		 MMUv2_MAX_STLB_ENTRIES);

	return 0;

fail_mem:
	if (etnaviv_domain->base.bad_page_cpu)
		dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
			    etnaviv_domain->base.bad_page_cpu,
			    etnaviv_domain->base.bad_page_dma);

	if (etnaviv_domain->pta_cpu)
		dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
			    etnaviv_domain->pta_cpu, etnaviv_domain->pta_dma);

	if (etnaviv_domain->mtlb_cpu)
		dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
			    etnaviv_domain->mtlb_cpu, etnaviv_domain->mtlb_dma);

	return ret;
}