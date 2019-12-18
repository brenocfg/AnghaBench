#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_ecc_stats {unsigned int corrected; } ;
struct denali_controller {int active_bank; scalar_t__ reg; } ;
struct TYPE_4__ {struct mtd_ecc_stats ecc_stats; } ;

/* Variables and functions */
 scalar_t__ ECC_COR_INFO (int) ; 
 int /*<<< orphan*/  ECC_COR_INFO__MAX_ERRORS ; 
 int ECC_COR_INFO__SHIFT (int) ; 
 int ECC_COR_INFO__UNCOR_ERR ; 
 unsigned int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 unsigned long GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 TYPE_2__* nand_to_mtd (struct nand_chip*) ; 
 struct denali_controller* to_denali_controller (struct nand_chip*) ; 

__attribute__((used)) static int denali_hw_ecc_fixup(struct nand_chip *chip,
			       unsigned long *uncor_ecc_flags)
{
	struct denali_controller *denali = to_denali_controller(chip);
	struct mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	int bank = denali->active_bank;
	u32 ecc_cor;
	unsigned int max_bitflips;

	ecc_cor = ioread32(denali->reg + ECC_COR_INFO(bank));
	ecc_cor >>= ECC_COR_INFO__SHIFT(bank);

	if (ecc_cor & ECC_COR_INFO__UNCOR_ERR) {
		/*
		 * This flag is set when uncorrectable error occurs at least in
		 * one ECC sector.  We can not know "how many sectors", or
		 * "which sector(s)".  We need erase-page check for all sectors.
		 */
		*uncor_ecc_flags = GENMASK(chip->ecc.steps - 1, 0);
		return 0;
	}

	max_bitflips = FIELD_GET(ECC_COR_INFO__MAX_ERRORS, ecc_cor);

	/*
	 * The register holds the maximum of per-sector corrected bitflips.
	 * This is suitable for the return value of the ->read_page() callback.
	 * Unfortunately, we can not know the total number of corrected bits in
	 * the page.  Increase the stats by max_bitflips. (compromised solution)
	 */
	ecc_stats->corrected += max_bitflips;

	return max_bitflips;
}