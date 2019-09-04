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
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;
struct marvell_nfc {scalar_t__ regs; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ NDCR ; 
 int NDCR_DWIDTH_C ; 
 int NDCR_DWIDTH_M ; 
 int readl_relaxed (scalar_t__) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void marvell_nfc_force_byte_access(struct nand_chip *chip,
					  bool force_8bit)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr;

	/*
	 * Callers of this function do not verify if the NAND is using a 16-bit
	 * an 8-bit bus for normal operations, so we need to take care of that
	 * here by leaving the configuration unchanged if the NAND does not have
	 * the NAND_BUSWIDTH_16 flag set.
	 */
	if (!(chip->options & NAND_BUSWIDTH_16))
		return;

	ndcr = readl_relaxed(nfc->regs + NDCR);

	if (force_8bit)
		ndcr &= ~(NDCR_DWIDTH_M | NDCR_DWIDTH_C);
	else
		ndcr |= NDCR_DWIDTH_M | NDCR_DWIDTH_C;

	writel_relaxed(ndcr, nfc->regs + NDCR);
}