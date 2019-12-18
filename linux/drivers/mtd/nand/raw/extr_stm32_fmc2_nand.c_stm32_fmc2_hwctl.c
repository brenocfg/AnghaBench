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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_fmc2_nfc {int /*<<< orphan*/  complete; scalar_t__ io_base; } ;
struct TYPE_2__ {scalar_t__ strength; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ FMC2_ECC_HAM ; 
 scalar_t__ FMC2_PCR ; 
 int /*<<< orphan*/  FMC2_PCR_WEN ; 
 int NAND_ECC_WRITE ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_fmc2_clear_bch_irq (struct stm32_fmc2_nfc*) ; 
 int /*<<< orphan*/  stm32_fmc2_enable_bch_irq (struct stm32_fmc2_nfc*,int) ; 
 int /*<<< orphan*/  stm32_fmc2_set_ecc (struct stm32_fmc2_nfc*,int) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_hwctl(struct nand_chip *chip, int mode)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);

	stm32_fmc2_set_ecc(fmc2, false);

	if (chip->ecc.strength != FMC2_ECC_HAM) {
		u32 pcr = readl_relaxed(fmc2->io_base + FMC2_PCR);

		if (mode == NAND_ECC_WRITE)
			pcr |= FMC2_PCR_WEN;
		else
			pcr &= ~FMC2_PCR_WEN;
		writel_relaxed(pcr, fmc2->io_base + FMC2_PCR);

		reinit_completion(&fmc2->complete);
		stm32_fmc2_clear_bch_irq(fmc2);
		stm32_fmc2_enable_bch_irq(fmc2, mode);
	}

	stm32_fmc2_set_ecc(fmc2, true);
}