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
typedef  int uint32_t ;
struct nand_chip {int dummy; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 int SLCCFG_CE_LOW ; 
 int /*<<< orphan*/  SLC_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CMD (int /*<<< orphan*/ ) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_nand_cmd_ctrl(struct nand_chip *chip, int cmd,
				  unsigned int ctrl)
{
	uint32_t tmp;
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Does CE state need to be changed? */
	tmp = readl(SLC_CFG(host->io_base));
	if (ctrl & NAND_NCE)
		tmp |= SLCCFG_CE_LOW;
	else
		tmp &= ~SLCCFG_CE_LOW;
	writel(tmp, SLC_CFG(host->io_base));

	if (cmd != NAND_CMD_NONE) {
		if (ctrl & NAND_CLE)
			writel(cmd, SLC_CMD(host->io_base));
		else
			writel(cmd, SLC_ADDR(host->io_base));
	}
}