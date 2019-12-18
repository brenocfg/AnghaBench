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
struct protection_domain {int dummy; } ;
struct page {int dummy; } ;
struct dma_ops_domain {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ IS_ERR (struct protection_domain*) ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unmap_single (struct dma_ops_domain*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_from_contiguous (struct device*,struct page*,size_t) ; 
 struct protection_domain* get_domain (struct device*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 struct dma_ops_domain* to_dma_ops_domain (struct protection_domain*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void free_coherent(struct device *dev, size_t size,
			  void *virt_addr, dma_addr_t dma_addr,
			  unsigned long attrs)
{
	struct protection_domain *domain;
	struct dma_ops_domain *dma_dom;
	struct page *page;

	page = virt_to_page(virt_addr);
	size = PAGE_ALIGN(size);

	domain = get_domain(dev);
	if (IS_ERR(domain))
		goto free_mem;

	dma_dom = to_dma_ops_domain(domain);

	__unmap_single(dma_dom, dma_addr, size, DMA_BIDIRECTIONAL);

free_mem:
	if (!dma_release_from_contiguous(dev, page, size >> PAGE_SHIFT))
		__free_pages(page, get_order(size));
}