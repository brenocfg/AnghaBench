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
struct ioc {TYPE_1__* sac_only_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct ioc*) ; 
 struct ioc* GET_IOC (struct device*) ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sba_map_single_attrs (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *
sba_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle,
		   gfp_t flags, unsigned long attrs)
{
	struct ioc *ioc;
	void *addr;

	ioc = GET_IOC(dev);
	ASSERT(ioc);

#ifdef CONFIG_NUMA
	{
		struct page *page;

		page = alloc_pages_node(ioc->node, flags, get_order(size));
		if (unlikely(!page))
			return NULL;

		addr = page_address(page);
	}
#else
	addr = (void *) __get_free_pages(flags, get_order(size));
#endif
	if (unlikely(!addr))
		return NULL;

	memset(addr, 0, size);
	*dma_handle = virt_to_phys(addr);

#ifdef ALLOW_IOV_BYPASS
	ASSERT(dev->coherent_dma_mask);
	/*
 	** Check if the PCI device can DMA to ptr... if so, just return ptr
 	*/
	if (likely((*dma_handle & ~dev->coherent_dma_mask) == 0)) {
		DBG_BYPASS("sba_alloc_coherent() bypass mask/addr: 0x%lx/0x%lx\n",
		           dev->coherent_dma_mask, *dma_handle);

		return addr;
	}
#endif

	/*
	 * If device can't bypass or bypass is disabled, pass the 32bit fake
	 * device to map single to get an iova mapping.
	 */
	*dma_handle = sba_map_single_attrs(&ioc->sac_only_dev->dev, addr,
					   size, 0, 0);

	return addr;
}