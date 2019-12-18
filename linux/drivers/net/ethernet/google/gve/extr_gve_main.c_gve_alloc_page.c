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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

int gve_alloc_page(struct device *dev, struct page **page, dma_addr_t *dma,
		   enum dma_data_direction dir)
{
	*page = alloc_page(GFP_KERNEL);
	if (!*page)
		return -ENOMEM;
	*dma = dma_map_page(dev, *page, 0, PAGE_SIZE, dir);
	if (dma_mapping_error(dev, *dma)) {
		put_page(*page);
		return -ENOMEM;
	}
	return 0;
}