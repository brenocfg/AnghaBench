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
typedef  int u8 ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;

/* Variables and functions */
#define  NAND_ECC_STATUS_1_3_CORRECTED 131 
#define  NAND_ECC_STATUS_4_6_CORRECTED 130 
#define  NAND_ECC_STATUS_7_8_CORRECTED 129 
 int NAND_ECC_STATUS_MASK ; 
#define  NAND_ECC_STATUS_UNCORRECTABLE 128 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int micron_nand_on_die_ecc_status_8(struct nand_chip *chip, u8 status)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/*
	 * With 8/512 we have more information but still don't know precisely
	 * how many bit-flips were seen.
	 */
	switch (status & NAND_ECC_STATUS_MASK) {
	case NAND_ECC_STATUS_UNCORRECTABLE:
		mtd->ecc_stats.failed++;
		return 0;
	case NAND_ECC_STATUS_1_3_CORRECTED:
		mtd->ecc_stats.corrected += 3;
		return 3;
	case NAND_ECC_STATUS_4_6_CORRECTED:
		mtd->ecc_stats.corrected += 6;
		/* rewrite recommended */
		return 6;
	case NAND_ECC_STATUS_7_8_CORRECTED:
		mtd->ecc_stats.corrected += 8;
		/* rewrite recommended */
		return 8;
	default:
		return 0;
	}
}