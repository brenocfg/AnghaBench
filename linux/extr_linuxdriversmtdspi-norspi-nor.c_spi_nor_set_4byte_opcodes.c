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
struct TYPE_2__ {int /*<<< orphan*/  erasesize; } ;
struct spi_nor {int /*<<< orphan*/  erase_opcode; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  read_opcode; TYPE_1__ mtd; } ;
struct flash_info {int /*<<< orphan*/  sector_size; } ;

/* Variables and functions */
 int JEDEC_MFR (struct flash_info const*) ; 
#define  SNOR_MFR_SPANSION 128 
 int /*<<< orphan*/  SPINOR_OP_SE ; 
 int /*<<< orphan*/  spi_nor_convert_3to4_erase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_convert_3to4_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_convert_3to4_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_nor_set_4byte_opcodes(struct spi_nor *nor,
				      const struct flash_info *info)
{
	/* Do some manufacturer fixups first */
	switch (JEDEC_MFR(info)) {
	case SNOR_MFR_SPANSION:
		/* No small sector erase for 4-byte command set */
		nor->erase_opcode = SPINOR_OP_SE;
		nor->mtd.erasesize = info->sector_size;
		break;

	default:
		break;
	}

	nor->read_opcode = spi_nor_convert_3to4_read(nor->read_opcode);
	nor->program_opcode = spi_nor_convert_3to4_program(nor->program_opcode);
	nor->erase_opcode = spi_nor_convert_3to4_erase(nor->erase_opcode);
}