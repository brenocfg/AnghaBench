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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBU_NAND_WAIT ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int NAND_WAIT_WR_C ; 
 int /*<<< orphan*/  NAND_WRITE_ADDR ; 
 int /*<<< orphan*/  NAND_WRITE_CMD ; 
 int ltq_ebu_r32 (int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  xway_writeb (struct mtd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xway_cmd_ctrl(struct nand_chip *chip, int cmd, unsigned int ctrl)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		xway_writeb(mtd, NAND_WRITE_CMD, cmd);
	else if (ctrl & NAND_ALE)
		xway_writeb(mtd, NAND_WRITE_ADDR, cmd);

	while ((ltq_ebu_r32(EBU_NAND_WAIT) & NAND_WAIT_WR_C) == 0)
		;
}