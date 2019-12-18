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
struct spi_nor_erase_type {int size_mask; } ;
struct spi_nor_erase_region {int size; } ;

/* Variables and functions */
 int const BIT (int) ; 
 int SNOR_ERASE_TYPE_MAX ; 
 int /*<<< orphan*/  spi_nor_region_mark_overlay (struct spi_nor_erase_region*) ; 

__attribute__((used)) static void
spi_nor_region_check_overlay(struct spi_nor_erase_region *region,
			     const struct spi_nor_erase_type *erase,
			     const u8 erase_type)
{
	int i;

	for (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) {
		if (!(erase_type & BIT(i)))
			continue;
		if (region->size & erase[i].size_mask) {
			spi_nor_region_mark_overlay(region);
			return;
		}
	}
}