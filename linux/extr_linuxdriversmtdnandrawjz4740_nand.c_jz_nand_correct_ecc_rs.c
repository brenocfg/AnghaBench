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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct mtd_info {int dummy; } ;
struct jz_nand {scalar_t__ base; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ETIMEDOUT ; 
 int JZ_NAND_ECC_CTRL_ENABLE ; 
 int JZ_NAND_ECC_CTRL_PAR_READY ; 
 int JZ_NAND_STATUS_DEC_FINISH ; 
 int JZ_NAND_STATUS_ERROR ; 
 int JZ_NAND_STATUS_ERR_COUNT ; 
 int JZ_NAND_STATUS_UNCOR_ERROR ; 
 scalar_t__ JZ_REG_NAND_ECC_CTRL ; 
 scalar_t__ JZ_REG_NAND_ERR (int) ; 
 scalar_t__ JZ_REG_NAND_IRQ_STAT ; 
 scalar_t__ JZ_REG_NAND_PAR0 ; 
 int /*<<< orphan*/  jz_nand_correct_data (int /*<<< orphan*/ *,int,int) ; 
 struct jz_nand* mtd_to_jz_nand (struct mtd_info*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int jz_nand_correct_ecc_rs(struct mtd_info *mtd, uint8_t *dat,
	uint8_t *read_ecc, uint8_t *calc_ecc)
{
	struct jz_nand *nand = mtd_to_jz_nand(mtd);
	int i, error_count, index;
	uint32_t reg, status, error;
	unsigned int timeout = 1000;

	for (i = 0; i < 9; ++i)
		writeb(read_ecc[i], nand->base + JZ_REG_NAND_PAR0 + i);

	reg = readl(nand->base + JZ_REG_NAND_ECC_CTRL);
	reg |= JZ_NAND_ECC_CTRL_PAR_READY;
	writel(reg, nand->base + JZ_REG_NAND_ECC_CTRL);

	do {
		status = readl(nand->base + JZ_REG_NAND_IRQ_STAT);
	} while (!(status & JZ_NAND_STATUS_DEC_FINISH) && --timeout);

	if (timeout == 0)
		return -ETIMEDOUT;

	reg = readl(nand->base + JZ_REG_NAND_ECC_CTRL);
	reg &= ~JZ_NAND_ECC_CTRL_ENABLE;
	writel(reg, nand->base + JZ_REG_NAND_ECC_CTRL);

	if (status & JZ_NAND_STATUS_ERROR) {
		if (status & JZ_NAND_STATUS_UNCOR_ERROR)
			return -EBADMSG;

		error_count = (status & JZ_NAND_STATUS_ERR_COUNT) >> 29;

		for (i = 0; i < error_count; ++i) {
			error = readl(nand->base + JZ_REG_NAND_ERR(i));
			index = ((error >> 16) & 0x1ff) - 1;
			if (index >= 0 && index < 512)
				jz_nand_correct_data(dat, index, error & 0x1ff);
		}

		return error_count;
	}

	return 0;
}