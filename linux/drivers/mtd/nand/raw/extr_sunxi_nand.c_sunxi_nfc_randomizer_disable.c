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
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int NAND_NEED_SCRAMBLING ; 
 int NFC_RANDOM_EN ; 
 scalar_t__ NFC_REG_ECC_CTL ; 
 int readl (scalar_t__) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sunxi_nfc_randomizer_disable(struct nand_chip *nand)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	if (!(nand->options & NAND_NEED_SCRAMBLING))
		return;

	writel(readl(nfc->regs + NFC_REG_ECC_CTL) & ~NFC_RANDOM_EN,
	       nfc->regs + NFC_REG_ECC_CTL);
}