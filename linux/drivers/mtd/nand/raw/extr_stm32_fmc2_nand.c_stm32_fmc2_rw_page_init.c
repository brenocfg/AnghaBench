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
struct stm32_fmc2_nfc {scalar_t__ io_base; int /*<<< orphan*/  cs_sel; } ;
struct TYPE_2__ {scalar_t__ steps; } ;
struct nand_chip {int options; TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int FMC2_BBM_LEN ; 
 scalar_t__ FMC2_CSQAR1 ; 
 scalar_t__ FMC2_CSQAR2 ; 
 int FMC2_CSQCAR1_ADDC3 (int) ; 
 int FMC2_CSQCAR1_ADDC4 (int) ; 
 int FMC2_CSQCAR2_ADDC5 (int) ; 
 int FMC2_CSQCAR2_NANDCEN (int /*<<< orphan*/ ) ; 
 int FMC2_CSQCAR2_SAO (int) ; 
 scalar_t__ FMC2_CSQCFGR1 ; 
 int FMC2_CSQCFGR1_ACYNBR (int) ; 
 int FMC2_CSQCFGR1_CMD1 (int /*<<< orphan*/ ) ; 
 int FMC2_CSQCFGR1_CMD1T ; 
 int FMC2_CSQCFGR1_CMD2 (int /*<<< orphan*/ ) ; 
 int FMC2_CSQCFGR1_CMD2EN ; 
 int FMC2_CSQCFGR1_CMD2T ; 
 int FMC2_CSQCFGR1_DMADEN ; 
 scalar_t__ FMC2_CSQCFGR2 ; 
 int FMC2_CSQCFGR2_DMASEN ; 
 int FMC2_CSQCFGR2_RCMD1 (int /*<<< orphan*/ ) ; 
 int FMC2_CSQCFGR2_RCMD1T ; 
 int FMC2_CSQCFGR2_RCMD2 (int /*<<< orphan*/ ) ; 
 int FMC2_CSQCFGR2_RCMD2EN ; 
 int FMC2_CSQCFGR2_RCMD2T ; 
 int FMC2_CSQCFGR2_SQSDTEN ; 
 scalar_t__ FMC2_CSQCFGR3 ; 
 int FMC2_CSQCFGR3_AC4T ; 
 int FMC2_CSQCFGR3_AC5T ; 
 int FMC2_CSQCFGR3_RAC2T ; 
 int FMC2_CSQCFGR3_SNBR (scalar_t__) ; 
 scalar_t__ FMC2_PCR ; 
 int FMC2_PCR_WEN ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_READSTART ; 
 int /*<<< orphan*/  NAND_CMD_RNDIN ; 
 int /*<<< orphan*/  NAND_CMD_RNDOUT ; 
 int /*<<< orphan*/  NAND_CMD_RNDOUTSTART ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 int NAND_ROW_ADDR_3 ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int readl_relaxed (scalar_t__) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_rw_page_init(struct nand_chip *chip, int page,
				    int raw, bool write_data)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	struct mtd_info *mtd = nand_to_mtd(chip);
	u32 csqcfgr1, csqcfgr2, csqcfgr3;
	u32 csqar1, csqar2;
	u32 ecc_offset = mtd->writesize + FMC2_BBM_LEN;
	u32 pcr = readl_relaxed(fmc2->io_base + FMC2_PCR);

	if (write_data)
		pcr |= FMC2_PCR_WEN;
	else
		pcr &= ~FMC2_PCR_WEN;
	writel_relaxed(pcr, fmc2->io_base + FMC2_PCR);

	/*
	 * - Set Program Page/Page Read command
	 * - Enable DMA request data
	 * - Set timings
	 */
	csqcfgr1 = FMC2_CSQCFGR1_DMADEN | FMC2_CSQCFGR1_CMD1T;
	if (write_data)
		csqcfgr1 |= FMC2_CSQCFGR1_CMD1(NAND_CMD_SEQIN);
	else
		csqcfgr1 |= FMC2_CSQCFGR1_CMD1(NAND_CMD_READ0) |
			    FMC2_CSQCFGR1_CMD2EN |
			    FMC2_CSQCFGR1_CMD2(NAND_CMD_READSTART) |
			    FMC2_CSQCFGR1_CMD2T;

	/*
	 * - Set Random Data Input/Random Data Read command
	 * - Enable the sequencer to access the Spare data area
	 * - Enable  DMA request status decoding for read
	 * - Set timings
	 */
	if (write_data)
		csqcfgr2 = FMC2_CSQCFGR2_RCMD1(NAND_CMD_RNDIN);
	else
		csqcfgr2 = FMC2_CSQCFGR2_RCMD1(NAND_CMD_RNDOUT) |
			   FMC2_CSQCFGR2_RCMD2EN |
			   FMC2_CSQCFGR2_RCMD2(NAND_CMD_RNDOUTSTART) |
			   FMC2_CSQCFGR2_RCMD1T |
			   FMC2_CSQCFGR2_RCMD2T;
	if (!raw) {
		csqcfgr2 |= write_data ? 0 : FMC2_CSQCFGR2_DMASEN;
		csqcfgr2 |= FMC2_CSQCFGR2_SQSDTEN;
	}

	/*
	 * - Set the number of sectors to be written
	 * - Set timings
	 */
	csqcfgr3 = FMC2_CSQCFGR3_SNBR(chip->ecc.steps - 1);
	if (write_data) {
		csqcfgr3 |= FMC2_CSQCFGR3_RAC2T;
		if (chip->options & NAND_ROW_ADDR_3)
			csqcfgr3 |= FMC2_CSQCFGR3_AC5T;
		else
			csqcfgr3 |= FMC2_CSQCFGR3_AC4T;
	}

	/*
	 * Set the fourth first address cycles
	 * Byte 1 and byte 2 => column, we start at 0x0
	 * Byte 3 and byte 4 => page
	 */
	csqar1 = FMC2_CSQCAR1_ADDC3(page);
	csqar1 |= FMC2_CSQCAR1_ADDC4(page >> 8);

	/*
	 * - Set chip enable number
	 * - Set ECC byte offset in the spare area
	 * - Calculate the number of address cycles to be issued
	 * - Set byte 5 of address cycle if needed
	 */
	csqar2 = FMC2_CSQCAR2_NANDCEN(fmc2->cs_sel);
	if (chip->options & NAND_BUSWIDTH_16)
		csqar2 |= FMC2_CSQCAR2_SAO(ecc_offset >> 1);
	else
		csqar2 |= FMC2_CSQCAR2_SAO(ecc_offset);
	if (chip->options & NAND_ROW_ADDR_3) {
		csqcfgr1 |= FMC2_CSQCFGR1_ACYNBR(5);
		csqar2 |= FMC2_CSQCAR2_ADDC5(page >> 16);
	} else {
		csqcfgr1 |= FMC2_CSQCFGR1_ACYNBR(4);
	}

	writel_relaxed(csqcfgr1, fmc2->io_base + FMC2_CSQCFGR1);
	writel_relaxed(csqcfgr2, fmc2->io_base + FMC2_CSQCFGR2);
	writel_relaxed(csqcfgr3, fmc2->io_base + FMC2_CSQCFGR3);
	writel_relaxed(csqar1, fmc2->io_base + FMC2_CSQAR1);
	writel_relaxed(csqar2, fmc2->io_base + FMC2_CSQAR2);
}