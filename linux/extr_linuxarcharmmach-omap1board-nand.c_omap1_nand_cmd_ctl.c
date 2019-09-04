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
struct nand_chip {scalar_t__ IO_ADDR_W; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void omap1_nand_cmd_ctl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	unsigned long mask;

	if (cmd == NAND_CMD_NONE)
		return;

	mask = (ctrl & NAND_CLE) ? 0x02 : 0;
	if (ctrl & NAND_ALE)
		mask |= 0x04;

	writeb(cmd, this->IO_ADDR_W + mask);
}