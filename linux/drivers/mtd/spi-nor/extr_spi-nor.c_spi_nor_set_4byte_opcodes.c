#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_erase_type {void* opcode; } ;
struct spi_nor_erase_map {struct spi_nor_erase_type* erase_type; } ;
struct TYPE_2__ {struct spi_nor_erase_map erase_map; } ;
struct spi_nor {TYPE_1__ params; void* erase_opcode; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  read_opcode; } ;

/* Variables and functions */
 int SNOR_ERASE_TYPE_MAX ; 
 void* spi_nor_convert_3to4_erase (void*) ; 
 int /*<<< orphan*/  spi_nor_convert_3to4_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_convert_3to4_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_has_uniform_erase (struct spi_nor*) ; 

__attribute__((used)) static void spi_nor_set_4byte_opcodes(struct spi_nor *nor)
{
	nor->read_opcode = spi_nor_convert_3to4_read(nor->read_opcode);
	nor->program_opcode = spi_nor_convert_3to4_program(nor->program_opcode);
	nor->erase_opcode = spi_nor_convert_3to4_erase(nor->erase_opcode);

	if (!spi_nor_has_uniform_erase(nor)) {
		struct spi_nor_erase_map *map = &nor->params.erase_map;
		struct spi_nor_erase_type *erase;
		int i;

		for (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) {
			erase = &map->erase_type[i];
			erase->opcode =
				spi_nor_convert_3to4_erase(erase->opcode);
		}
	}
}