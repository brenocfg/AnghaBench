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
typedef  int u8 ;
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct fsmc_nand_data {scalar_t__ regs_va; } ;

/* Variables and functions */
 scalar_t__ ECC1 ; 
 struct fsmc_nand_data* nand_to_fsmc (struct nand_chip*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int fsmc_read_hwecc_ecc1(struct nand_chip *chip, const u8 *data,
				u8 *ecc)
{
	struct fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 ecc_tmp;

	ecc_tmp = readl_relaxed(host->regs_va + ECC1);
	ecc[0] = ecc_tmp;
	ecc[1] = ecc_tmp >> 8;
	ecc[2] = ecc_tmp >> 16;

	return 0;
}