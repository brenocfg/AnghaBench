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
typedef  int u8 ;
struct spi_nor_erase_region {int offset; } ;
struct spi_nor_erase_map {struct spi_nor_erase_region* regions; } ;

/* Variables and functions */
 int SNOR_ERASE_TYPE_MASK ; 
 struct spi_nor_erase_region* spi_nor_region_next (struct spi_nor_erase_region*) ; 
 int spi_nor_sort_erase_mask (struct spi_nor_erase_map*,int) ; 

__attribute__((used)) static void spi_nor_regions_sort_erase_types(struct spi_nor_erase_map *map)
{
	struct spi_nor_erase_region *region = map->regions;
	u8 region_erase_mask, sorted_erase_mask;

	while (region) {
		region_erase_mask = region->offset & SNOR_ERASE_TYPE_MASK;

		sorted_erase_mask = spi_nor_sort_erase_mask(map,
							    region_erase_mask);

		/* Overwrite erase mask. */
		region->offset = (region->offset & ~SNOR_ERASE_TYPE_MASK) |
				 sorted_erase_mask;

		region = spi_nor_region_next(region);
	}
}