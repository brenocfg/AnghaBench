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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct mtd_info {int dummy; } ;
struct fsmc_nand_data {scalar_t__ regs_va; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ECC1 ; 
 scalar_t__ ECC2 ; 
 scalar_t__ ECC3 ; 
 int ETIMEDOUT ; 
 unsigned long FSMC_BUSY_WAIT_TIMEOUT ; 
 int FSMC_CODE_RDY ; 
 scalar_t__ STS ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int fsmc_read_hwecc_ecc4(struct mtd_info *mtd, const uint8_t *data,
				uint8_t *ecc)
{
	struct fsmc_nand_data *host = mtd_to_fsmc(mtd);
	uint32_t ecc_tmp;
	unsigned long deadline = jiffies + FSMC_BUSY_WAIT_TIMEOUT;

	do {
		if (readl_relaxed(host->regs_va + STS) & FSMC_CODE_RDY)
			break;
		else
			cond_resched();
	} while (!time_after_eq(jiffies, deadline));

	if (time_after_eq(jiffies, deadline)) {
		dev_err(host->dev, "calculate ecc timed out\n");
		return -ETIMEDOUT;
	}

	ecc_tmp = readl_relaxed(host->regs_va + ECC1);
	ecc[0] = (uint8_t) (ecc_tmp >> 0);
	ecc[1] = (uint8_t) (ecc_tmp >> 8);
	ecc[2] = (uint8_t) (ecc_tmp >> 16);
	ecc[3] = (uint8_t) (ecc_tmp >> 24);

	ecc_tmp = readl_relaxed(host->regs_va + ECC2);
	ecc[4] = (uint8_t) (ecc_tmp >> 0);
	ecc[5] = (uint8_t) (ecc_tmp >> 8);
	ecc[6] = (uint8_t) (ecc_tmp >> 16);
	ecc[7] = (uint8_t) (ecc_tmp >> 24);

	ecc_tmp = readl_relaxed(host->regs_va + ECC3);
	ecc[8] = (uint8_t) (ecc_tmp >> 0);
	ecc[9] = (uint8_t) (ecc_tmp >> 8);
	ecc[10] = (uint8_t) (ecc_tmp >> 16);
	ecc[11] = (uint8_t) (ecc_tmp >> 24);

	ecc_tmp = readl_relaxed(host->regs_va + STS);
	ecc[12] = (uint8_t) (ecc_tmp >> 16);

	return 0;
}