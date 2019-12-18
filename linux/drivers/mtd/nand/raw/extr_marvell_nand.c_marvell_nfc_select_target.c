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
typedef  int u32 ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc {struct nand_chip* selected_chip; scalar_t__ regs; } ;
struct marvell_nand_chip {int ndcr; unsigned int selected_die; int ndtr0; int ndtr1; } ;

/* Variables and functions */
 scalar_t__ NDCR ; 
 int /*<<< orphan*/  NDCR_ALL_INT ; 
 int NDCR_GENERIC_FIELDS_MASK ; 
 int NDCR_ND_RUN ; 
 scalar_t__ NDTR0 ; 
 scalar_t__ NDTR1 ; 
 int /*<<< orphan*/  marvell_nfc_clear_int (struct marvell_nfc*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 struct marvell_nand_chip* to_marvell_nand (struct nand_chip*) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void marvell_nfc_select_target(struct nand_chip *chip,
				      unsigned int die_nr)
{
	struct marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr_generic;

	/*
	 * Reset the NDCR register to a clean state for this particular chip,
	 * also clear ND_RUN bit.
	 */
	ndcr_generic = readl_relaxed(nfc->regs + NDCR) &
		       NDCR_GENERIC_FIELDS_MASK & ~NDCR_ND_RUN;
	writel_relaxed(ndcr_generic | marvell_nand->ndcr, nfc->regs + NDCR);

	/* Also reset the interrupt status register */
	marvell_nfc_clear_int(nfc, NDCR_ALL_INT);

	if (chip == nfc->selected_chip && die_nr == marvell_nand->selected_die)
		return;

	writel_relaxed(marvell_nand->ndtr0, nfc->regs + NDTR0);
	writel_relaxed(marvell_nand->ndtr1, nfc->regs + NDTR1);

	nfc->selected_chip = chip;
	marvell_nand->selected_die = die_nr;
}