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
typedef  int /*<<< orphan*/  u64 ;
struct protection_domain {int dummy; } ;
struct page {int dummy; } ;
struct dma_ops_domain {int dummy; } ;
struct device {int /*<<< orphan*/ * dma_mask; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IS_ERR (struct protection_domain*) ; 
 int /*<<< orphan*/  PTR_ERR (struct protection_domain*) ; 
 int /*<<< orphan*/  __map_single (struct device*,struct dma_ops_domain*,scalar_t__,size_t,int,int /*<<< orphan*/ ) ; 
 struct protection_domain* get_domain (struct device*) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 struct dma_ops_domain* to_dma_ops_domain (struct protection_domain*) ; 

__attribute__((used)) static dma_addr_t map_page(struct device *dev, struct page *page,
			   unsigned long offset, size_t size,
			   enum dma_data_direction dir,
			   unsigned long attrs)
{
	phys_addr_t paddr = page_to_phys(page) + offset;
	struct protection_domain *domain;
	struct dma_ops_domain *dma_dom;
	u64 dma_mask;

	domain = get_domain(dev);
	if (PTR_ERR(domain) == -EINVAL)
		return (dma_addr_t)paddr;
	else if (IS_ERR(domain))
		return DMA_MAPPING_ERROR;

	dma_mask = *dev->dma_mask;
	dma_dom = to_dma_ops_domain(domain);

	return __map_single(dev, dma_dom, paddr, size, dir, dma_mask);
}