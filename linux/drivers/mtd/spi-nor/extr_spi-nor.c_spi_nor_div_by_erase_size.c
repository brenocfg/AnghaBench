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
typedef  int u64 ;
typedef  int u32 ;
struct spi_nor_erase_type {int size_mask; int size_shift; } ;

/* Variables and functions */

__attribute__((used)) static u64 spi_nor_div_by_erase_size(const struct spi_nor_erase_type *erase,
				     u64 dividend, u32 *remainder)
{
	/* JEDEC JESD216B Standard imposes erase sizes to be power of 2. */
	*remainder = (u32)dividend & erase->size_mask;
	return dividend >> erase->size_shift;
}