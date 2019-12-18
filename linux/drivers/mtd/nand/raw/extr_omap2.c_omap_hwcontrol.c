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
struct TYPE_2__ {int /*<<< orphan*/  gpmc_nand_data; int /*<<< orphan*/  gpmc_nand_address; int /*<<< orphan*/  gpmc_nand_command; } ;
struct omap_nand_info {TYPE_1__ reg; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 struct omap_nand_info* mtd_to_omap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_hwcontrol(struct nand_chip *chip, int cmd, unsigned int ctrl)
{
	struct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));

	if (cmd != NAND_CMD_NONE) {
		if (ctrl & NAND_CLE)
			writeb(cmd, info->reg.gpmc_nand_command);

		else if (ctrl & NAND_ALE)
			writeb(cmd, info->reg.gpmc_nand_address);

		else /* NAND_NCE */
			writeb(cmd, info->reg.gpmc_nand_data);
	}
}