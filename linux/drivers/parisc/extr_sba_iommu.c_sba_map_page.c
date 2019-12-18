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
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  sba_map_single (struct device*,scalar_t__,size_t,int) ; 

__attribute__((used)) static dma_addr_t
sba_map_page(struct device *dev, struct page *page, unsigned long offset,
		size_t size, enum dma_data_direction direction,
		unsigned long attrs)
{
	return sba_map_single(dev, page_address(page) + offset, size,
			direction);
}