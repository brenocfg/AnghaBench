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
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 scalar_t__ HEXAGON_MAPPING_ERROR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  check_addr (char*,struct device*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dma_addr_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  dma_sync (int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ page_to_phys (struct page*) ; 

__attribute__((used)) static dma_addr_t hexagon_map_page(struct device *dev, struct page *page,
				   unsigned long offset, size_t size,
				   enum dma_data_direction dir,
				   unsigned long attrs)
{
	dma_addr_t bus = page_to_phys(page) + offset;
	WARN_ON(size == 0);

	if (!check_addr("map_single", dev, bus, size))
		return HEXAGON_MAPPING_ERROR;

	if (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		dma_sync(dma_addr_to_virt(bus), size, dir);

	return bus;
}