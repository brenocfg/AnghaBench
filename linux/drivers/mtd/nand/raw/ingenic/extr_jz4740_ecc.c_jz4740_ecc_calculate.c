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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct ingenic_ecc_params {int bytes; } ;
struct ingenic_ecc {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int JZ_NAND_ECC_CTRL_ENABLE ; 
 int JZ_NAND_STATUS_ENC_FINISH ; 
 scalar_t__ JZ_REG_NAND_ECC_CTRL ; 
 scalar_t__ JZ_REG_NAND_IRQ_STAT ; 
 scalar_t__ JZ_REG_NAND_PAR0 ; 
 int /*<<< orphan*/  empty_block_ecc ; 
 int /*<<< orphan*/  jz4740_ecc_reset (struct ingenic_ecc*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int jz4740_ecc_calculate(struct ingenic_ecc *ecc,
				struct ingenic_ecc_params *params,
				const u8 *buf, u8 *ecc_code)
{
	uint32_t reg, status;
	unsigned int timeout = 1000;
	int i;

	jz4740_ecc_reset(ecc, true);

	do {
		status = readl(ecc->base + JZ_REG_NAND_IRQ_STAT);
	} while (!(status & JZ_NAND_STATUS_ENC_FINISH) && --timeout);

	if (timeout == 0)
		return -ETIMEDOUT;

	reg = readl(ecc->base + JZ_REG_NAND_ECC_CTRL);
	reg &= ~JZ_NAND_ECC_CTRL_ENABLE;
	writel(reg, ecc->base + JZ_REG_NAND_ECC_CTRL);

	for (i = 0; i < params->bytes; ++i)
		ecc_code[i] = readb(ecc->base + JZ_REG_NAND_PAR0 + i);

	/*
	 * If the written data is completely 0xff, we also want to write 0xff as
	 * ECC, otherwise we will get in trouble when doing subpage writes.
	 */
	if (memcmp(ecc_code, empty_block_ecc, ARRAY_SIZE(empty_block_ecc)) == 0)
		memset(ecc_code, 0xff, ARRAY_SIZE(empty_block_ecc));

	return 0;
}