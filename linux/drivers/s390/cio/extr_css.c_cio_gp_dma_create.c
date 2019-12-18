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
struct gen_pool {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_DMA_GFP ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_add_virt (struct gen_pool*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gen_pool* gen_pool_create (int,int) ; 

struct gen_pool *cio_gp_dma_create(struct device *dma_dev, int nr_pages)
{
	struct gen_pool *gp_dma;
	void *cpu_addr;
	dma_addr_t dma_addr;
	int i;

	gp_dma = gen_pool_create(3, -1);
	if (!gp_dma)
		return NULL;
	for (i = 0; i < nr_pages; ++i) {
		cpu_addr = dma_alloc_coherent(dma_dev, PAGE_SIZE, &dma_addr,
					      CIO_DMA_GFP);
		if (!cpu_addr)
			return gp_dma;
		gen_pool_add_virt(gp_dma, (unsigned long) cpu_addr,
				  dma_addr, PAGE_SIZE, -1);
	}
	return gp_dma;
}