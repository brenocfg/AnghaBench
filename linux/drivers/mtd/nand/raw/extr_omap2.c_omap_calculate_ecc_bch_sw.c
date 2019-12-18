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
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int _omap_calculate_ecc_bch (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int omap_calculate_ecc_bch_sw(struct nand_chip *chip,
				     const u_char *dat, u_char *ecc_calc)
{
	return _omap_calculate_ecc_bch(nand_to_mtd(chip), dat, ecc_calc, 0);
}