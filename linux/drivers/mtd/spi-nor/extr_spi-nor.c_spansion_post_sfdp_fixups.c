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
struct mtd_info {scalar_t__ size; int /*<<< orphan*/  erasesize; } ;
struct spi_nor {TYPE_1__* info; struct mtd_info mtd; int /*<<< orphan*/  erase_opcode; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNOR_F_4B_OPCODES ; 
 int /*<<< orphan*/  SPINOR_OP_SE ; 
 scalar_t__ SZ_16M ; 

__attribute__((used)) static void spansion_post_sfdp_fixups(struct spi_nor *nor)
{
	struct mtd_info *mtd = &nor->mtd;

	if (mtd->size <= SZ_16M)
		return;

	nor->flags |= SNOR_F_4B_OPCODES;
	/* No small sector erase for 4-byte command set */
	nor->erase_opcode = SPINOR_OP_SE;
	nor->mtd.erasesize = nor->info->sector_size;
}