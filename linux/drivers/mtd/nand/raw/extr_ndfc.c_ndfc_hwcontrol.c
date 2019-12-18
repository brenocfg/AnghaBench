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
struct ndfc_controller {scalar_t__ ndfcbase; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 scalar_t__ NDFC_ALE ; 
 scalar_t__ NDFC_CMD ; 
 struct ndfc_controller* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ndfc_hwcontrol(struct nand_chip *chip, int cmd, unsigned int ctrl)
{
	struct ndfc_controller *ndfc = nand_get_controller_data(chip);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writel(cmd & 0xFF, ndfc->ndfcbase + NDFC_CMD);
	else
		writel(cmd & 0xFF, ndfc->ndfcbase + NDFC_ALE);
}