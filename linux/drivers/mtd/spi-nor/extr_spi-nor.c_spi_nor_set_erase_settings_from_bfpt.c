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
struct spi_nor_erase_type {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_nor_set_erase_type (struct spi_nor_erase_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spi_nor_set_erase_settings_from_bfpt(struct spi_nor_erase_type *erase,
				     u32 size, u8 opcode, u8 i)
{
	erase->idx = i;
	spi_nor_set_erase_type(erase, size, opcode);
}