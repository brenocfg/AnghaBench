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
struct xway_nand_data {int /*<<< orphan*/  csflags; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EBU_NAND_CON ; 
 int /*<<< orphan*/  NAND_CON_CE ; 
 int /*<<< orphan*/  NAND_CON_NANDM ; 
 int /*<<< orphan*/  ebu_lock ; 
 int /*<<< orphan*/  ltq_ebu_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xway_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xway_select_chip(struct nand_chip *chip, int select)
{
	struct xway_nand_data *data = nand_get_controller_data(chip);

	switch (select) {
	case -1:
		ltq_ebu_w32_mask(NAND_CON_CE, 0, EBU_NAND_CON);
		ltq_ebu_w32_mask(NAND_CON_NANDM, 0, EBU_NAND_CON);
		spin_unlock_irqrestore(&ebu_lock, data->csflags);
		break;
	case 0:
		spin_lock_irqsave(&ebu_lock, data->csflags);
		ltq_ebu_w32_mask(0, NAND_CON_NANDM, EBU_NAND_CON);
		ltq_ebu_w32_mask(0, NAND_CON_CE, EBU_NAND_CON);
		break;
	default:
		BUG();
	}
}