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
struct stm32_fmc2_timings {int /*<<< orphan*/  thiz; int /*<<< orphan*/  thold_att; int /*<<< orphan*/  twait; int /*<<< orphan*/  tset_att; int /*<<< orphan*/  thold_mem; int /*<<< orphan*/  tset_mem; int /*<<< orphan*/  tar; int /*<<< orphan*/  tclr; } ;
struct stm32_fmc2_nfc {scalar_t__ io_base; } ;
struct stm32_fmc2_nand {struct stm32_fmc2_timings timings; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ FMC2_PATT ; 
 int /*<<< orphan*/  FMC2_PATT_ATTHIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PATT_ATTHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PATT_ATTSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PATT_ATTWAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ FMC2_PCR ; 
 int /*<<< orphan*/  FMC2_PCR_TAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_TAR_MASK ; 
 int /*<<< orphan*/  FMC2_PCR_TCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PCR_TCLR_MASK ; 
 scalar_t__ FMC2_PMEM ; 
 int /*<<< orphan*/  FMC2_PMEM_MEMHIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PMEM_MEMHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PMEM_MEMSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMC2_PMEM_MEMWAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct stm32_fmc2_nand* to_fmc2_nand (struct nand_chip*) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_timings_init(struct nand_chip *chip)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	struct stm32_fmc2_nand *nand = to_fmc2_nand(chip);
	struct stm32_fmc2_timings *timings = &nand->timings;
	u32 pcr = readl_relaxed(fmc2->io_base + FMC2_PCR);
	u32 pmem, patt;

	/* Set tclr/tar timings */
	pcr &= ~FMC2_PCR_TCLR_MASK;
	pcr |= FMC2_PCR_TCLR(timings->tclr);
	pcr &= ~FMC2_PCR_TAR_MASK;
	pcr |= FMC2_PCR_TAR(timings->tar);

	/* Set tset/twait/thold/thiz timings in common bank */
	pmem = FMC2_PMEM_MEMSET(timings->tset_mem);
	pmem |= FMC2_PMEM_MEMWAIT(timings->twait);
	pmem |= FMC2_PMEM_MEMHOLD(timings->thold_mem);
	pmem |= FMC2_PMEM_MEMHIZ(timings->thiz);

	/* Set tset/twait/thold/thiz timings in attribut bank */
	patt = FMC2_PATT_ATTSET(timings->tset_att);
	patt |= FMC2_PATT_ATTWAIT(timings->twait);
	patt |= FMC2_PATT_ATTHOLD(timings->thold_att);
	patt |= FMC2_PATT_ATTHIZ(timings->thiz);

	writel_relaxed(pcr, fmc2->io_base + FMC2_PCR);
	writel_relaxed(pmem, fmc2->io_base + FMC2_PMEM);
	writel_relaxed(patt, fmc2->io_base + FMC2_PATT);
}