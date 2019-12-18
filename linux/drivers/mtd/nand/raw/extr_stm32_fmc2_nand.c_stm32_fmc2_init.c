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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_fmc2_nfc {int cs_sel; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ FMC2_BCR1 ; 
 int /*<<< orphan*/  FMC2_BCR1_FMC2EN ; 
 scalar_t__ FMC2_PATT ; 
 int /*<<< orphan*/  FMC2_PATT_DEFAULT ; 
 scalar_t__ FMC2_PCR ; 
 int /*<<< orphan*/  FMC2_PCR_BCHECC ; 
 int /*<<< orphan*/  FMC2_PCR_ECCALG ; 
 int /*<<< orphan*/  FMC2_PCR_ECCEN ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS_2048 ; 
 int /*<<< orphan*/  FMC2_PCR_ECCSS_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_PBKEN ; 
 int /*<<< orphan*/  FMC2_PCR_PWAITEN ; 
 int /*<<< orphan*/  FMC2_PCR_PWID_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_TAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_TAR_DEFAULT ; 
 int /*<<< orphan*/  FMC2_PCR_TAR_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_TCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_TCLR_DEFAULT ; 
 int /*<<< orphan*/  FMC2_PCR_TCLR_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_WEN ; 
 scalar_t__ FMC2_PMEM ; 
 int /*<<< orphan*/  FMC2_PMEM_DEFAULT ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_init(struct stm32_fmc2_nfc *fmc2)
{
	u32 pcr = readl_relaxed(fmc2->io_base + FMC2_PCR);
	u32 bcr1 = readl_relaxed(fmc2->io_base + FMC2_BCR1);

	/* Set CS used to undefined */
	fmc2->cs_sel = -1;

	/* Enable wait feature and nand flash memory bank */
	pcr |= FMC2_PCR_PWAITEN;
	pcr |= FMC2_PCR_PBKEN;

	/* Set buswidth to 8 bits mode for identification */
	pcr &= ~FMC2_PCR_PWID_MASK;

	/* ECC logic is disabled */
	pcr &= ~FMC2_PCR_ECCEN;

	/* Default mode */
	pcr &= ~FMC2_PCR_ECCALG;
	pcr &= ~FMC2_PCR_BCHECC;
	pcr &= ~FMC2_PCR_WEN;

	/* Set default ECC sector size */
	pcr &= ~FMC2_PCR_ECCSS_MASK;
	pcr |= FMC2_PCR_ECCSS(FMC2_PCR_ECCSS_2048);

	/* Set default tclr/tar timings */
	pcr &= ~FMC2_PCR_TCLR_MASK;
	pcr |= FMC2_PCR_TCLR(FMC2_PCR_TCLR_DEFAULT);
	pcr &= ~FMC2_PCR_TAR_MASK;
	pcr |= FMC2_PCR_TAR(FMC2_PCR_TAR_DEFAULT);

	/* Enable FMC2 controller */
	bcr1 |= FMC2_BCR1_FMC2EN;

	writel_relaxed(bcr1, fmc2->io_base + FMC2_BCR1);
	writel_relaxed(pcr, fmc2->io_base + FMC2_PCR);
	writel_relaxed(FMC2_PMEM_DEFAULT, fmc2->io_base + FMC2_PMEM);
	writel_relaxed(FMC2_PATT_DEFAULT, fmc2->io_base + FMC2_PATT);
}