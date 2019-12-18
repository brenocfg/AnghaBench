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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct spi_nor_erase_type {scalar_t__ size; } ;
struct spi_nor_erase_region {int offset; } ;
struct spi_nor_erase_map {struct spi_nor_erase_type* erase_type; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SNOR_ERASE_TYPE_MASK ; 
 int SNOR_ERASE_TYPE_MAX ; 
 int SNOR_OVERLAID_REGION ; 
 int /*<<< orphan*/  spi_nor_div_by_erase_size (struct spi_nor_erase_type const*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static const struct spi_nor_erase_type *
spi_nor_find_best_erase_type(const struct spi_nor_erase_map *map,
			     const struct spi_nor_erase_region *region,
			     u64 addr, u32 len)
{
	const struct spi_nor_erase_type *erase;
	u32 rem;
	int i;
	u8 erase_mask = region->offset & SNOR_ERASE_TYPE_MASK;

	/*
	 * Erase types are ordered by size, with the smallest erase type at
	 * index 0.
	 */
	for (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) {
		/* Does the erase region support the tested erase type? */
		if (!(erase_mask & BIT(i)))
			continue;

		erase = &map->erase_type[i];

		/* Don't erase more than what the user has asked for. */
		if (erase->size > len)
			continue;

		/* Alignment is not mandatory for overlaid regions */
		if (region->offset & SNOR_OVERLAID_REGION)
			return erase;

		spi_nor_div_by_erase_size(erase, addr, &rem);
		if (rem)
			continue;
		else
			return erase;
	}

	return NULL;
}