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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mtd_info {int dummy; } ;
struct jz_nand {scalar_t__ base; scalar_t__ is_reading; } ;

/* Variables and functions */
 int JZ_NAND_ECC_CTRL_ENABLE ; 
 int JZ_NAND_STATUS_ENC_FINISH ; 
 scalar_t__ JZ_REG_NAND_ECC_CTRL ; 
 scalar_t__ JZ_REG_NAND_IRQ_STAT ; 
 scalar_t__ JZ_REG_NAND_PAR0 ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 struct jz_nand* mtd_to_jz_nand (struct mtd_info*) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int jz_nand_calculate_ecc_rs(struct mtd_info *mtd, const uint8_t *dat,
	uint8_t *ecc_code)
{
	struct jz_nand *nand = mtd_to_jz_nand(mtd);
	uint32_t reg, status;
	int i;
	unsigned int timeout = 1000;
	static uint8_t empty_block_ecc[] = {0xcd, 0x9d, 0x90, 0x58, 0xf4,
						0x8b, 0xff, 0xb7, 0x6f};

	if (nand->is_reading)
		return 0;

	do {
		status = readl(nand->base + JZ_REG_NAND_IRQ_STAT);
	} while (!(status & JZ_NAND_STATUS_ENC_FINISH) && --timeout);

	if (timeout == 0)
	    return -1;

	reg = readl(nand->base + JZ_REG_NAND_ECC_CTRL);
	reg &= ~JZ_NAND_ECC_CTRL_ENABLE;
	writel(reg, nand->base + JZ_REG_NAND_ECC_CTRL);

	for (i = 0; i < 9; ++i)
		ecc_code[i] = readb(nand->base + JZ_REG_NAND_PAR0 + i);

	/* If the written data is completly 0xff, we also want to write 0xff as
	 * ecc, otherwise we will get in trouble when doing subpage writes. */
	if (memcmp(ecc_code, empty_block_ecc, 9) == 0)
		memset(ecc_code, 0xff, 9);

	return 0;
}