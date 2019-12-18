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
typedef  int /*<<< orphan*/  u16 ;
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int NAND_NEED_SCRAMBLING ; 
 int NFC_RANDOM_SEED (int /*<<< orphan*/ ) ; 
 int NFC_RANDOM_SEED_MSK ; 
 scalar_t__ NFC_REG_ECC_CTL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_state (struct nand_chip*,int,int) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sunxi_nfc_randomizer_config(struct nand_chip *nand, int page,
					bool ecc)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u32 ecc_ctl = readl(nfc->regs + NFC_REG_ECC_CTL);
	u16 state;

	if (!(nand->options & NAND_NEED_SCRAMBLING))
		return;

	ecc_ctl = readl(nfc->regs + NFC_REG_ECC_CTL);
	state = sunxi_nfc_randomizer_state(nand, page, ecc);
	ecc_ctl = readl(nfc->regs + NFC_REG_ECC_CTL) & ~NFC_RANDOM_SEED_MSK;
	writel(ecc_ctl | NFC_RANDOM_SEED(state), nfc->regs + NFC_REG_ECC_CTL);
}