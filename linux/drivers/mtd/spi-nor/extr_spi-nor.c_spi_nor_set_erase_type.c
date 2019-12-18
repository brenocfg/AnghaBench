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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor_erase_type {int size_shift; int size_mask; int /*<<< orphan*/  size; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_nor_set_erase_type(struct spi_nor_erase_type *erase,
				   u32 size, u8 opcode)
{
	erase->size = size;
	erase->opcode = opcode;
	/* JEDEC JESD216B Standard imposes erase sizes to be power of 2. */
	erase->size_shift = ffs(erase->size) - 1;
	erase->size_mask = (1 << erase->size_shift) - 1;
}