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
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 scalar_t__ ECC1 ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int fsmc_read_hwecc_ecc1(struct mtd_info *mtd, const uint8_t *data,
				uint8_t *ecc)
{
	struct fsmc_nand_data *host = mtd_to_fsmc(mtd);
	uint32_t ecc_tmp;

	ecc_tmp = readl_relaxed(host->regs_va + ECC1);
	ecc[0] = (uint8_t) (ecc_tmp >> 0);
	ecc[1] = (uint8_t) (ecc_tmp >> 8);
	ecc[2] = (uint8_t) (ecc_tmp >> 16);

	return 0;
}