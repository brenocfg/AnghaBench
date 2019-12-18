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
 int /*<<< orphan*/  dma_map_page_attrs (int /*<<< orphan*/ ,struct page*,unsigned long,size_t,int,unsigned long) ; 
 int /*<<< orphan*/  to_vmd_dev (struct device*) ; 

__attribute__((used)) static dma_addr_t vmd_map_page(struct device *dev, struct page *page,
			       unsigned long offset, size_t size,
			       enum dma_data_direction dir,
			       unsigned long attrs)
{
	return dma_map_page_attrs(to_vmd_dev(dev), page, offset, size, dir,
			attrs);
}