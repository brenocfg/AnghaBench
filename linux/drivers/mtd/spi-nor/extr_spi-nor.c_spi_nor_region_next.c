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
struct spi_nor_erase_region {int dummy; } ;

/* Variables and functions */
 scalar_t__ spi_nor_region_is_last (struct spi_nor_erase_region*) ; 

__attribute__((used)) static struct spi_nor_erase_region *
spi_nor_region_next(struct spi_nor_erase_region *region)
{
	if (spi_nor_region_is_last(region))
		return NULL;
	region++;
	return region;
}