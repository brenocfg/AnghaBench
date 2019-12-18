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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ algo; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct marvell_nfc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ NAND_ECC_BCH ; 
 scalar_t__ NDCR ; 
 int NDCR_ECC_EN ; 
 scalar_t__ NDECCCTRL ; 
 int readl_relaxed (scalar_t__) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void marvell_nfc_disable_hw_ecc(struct nand_chip *chip)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr = readl_relaxed(nfc->regs + NDCR);

	if (ndcr & NDCR_ECC_EN) {
		writel_relaxed(ndcr & ~NDCR_ECC_EN, nfc->regs + NDCR);
		if (chip->ecc.algo == NAND_ECC_BCH)
			writel_relaxed(0, nfc->regs + NDECCCTRL);
	}
}