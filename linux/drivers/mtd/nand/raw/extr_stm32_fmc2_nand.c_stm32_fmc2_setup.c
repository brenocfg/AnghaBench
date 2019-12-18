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
struct stm32_fmc2_nfc {scalar_t__ io_base; } ;
struct TYPE_2__ {scalar_t__ strength; } ;
struct nand_chip {int options; TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ FMC2_ECC_BCH4 ; 
 scalar_t__ FMC2_ECC_BCH8 ; 
 scalar_t__ FMC2_PCR ; 
 int /*<<< orphan*/  FMC2_PCR_BCHECC ; 
 int /*<<< orphan*/  FMC2_PCR_ECCALG ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS_512 ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_PWID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_PWID_BUSWIDTH_16 ; 
 int /*<<< orphan*/  FMC2_PCR_PWID_MASK ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_setup(struct nand_chip *chip)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	u32 pcr = readl_relaxed(fmc2->io_base + FMC2_PCR);

	/* Configure ECC algorithm (default configuration is Hamming) */
	pcr &= ~FMC2_PCR_ECCALG;
	pcr &= ~FMC2_PCR_BCHECC;
	if (chip->ecc.strength == FMC2_ECC_BCH8) {
		pcr |= FMC2_PCR_ECCALG;
		pcr |= FMC2_PCR_BCHECC;
	} else if (chip->ecc.strength == FMC2_ECC_BCH4) {
		pcr |= FMC2_PCR_ECCALG;
	}

	/* Set buswidth */
	pcr &= ~FMC2_PCR_PWID_MASK;
	if (chip->options & NAND_BUSWIDTH_16)
		pcr |= FMC2_PCR_PWID(FMC2_PCR_PWID_BUSWIDTH_16);

	/* Set ECC sector size */
	pcr &= ~FMC2_PCR_ECCSS_MASK;
	pcr |= FMC2_PCR_ECCSS(FMC2_PCR_ECCSS_512);

	writel_relaxed(pcr, fmc2->io_base + FMC2_PCR);
}