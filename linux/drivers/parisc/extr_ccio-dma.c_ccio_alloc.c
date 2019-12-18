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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccio_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  hwdev ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void * 
ccio_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flag,
		unsigned long attrs)
{
      void *ret;
#if 0
/* GRANT Need to establish hierarchy for non-PCI devs as well
** and then provide matching gsc_map_xxx() functions for them as well.
*/
	if(!hwdev) {
		/* only support PCI */
		*dma_handle = 0;
		return 0;
	}
#endif
        ret = (void *) __get_free_pages(flag, get_order(size));

	if (ret) {
		memset(ret, 0, size);
		*dma_handle = ccio_map_single(dev, ret, size, PCI_DMA_BIDIRECTIONAL);
	}

	return ret;
}