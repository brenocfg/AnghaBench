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
struct TYPE_2__ {int mode; int algo; int strength; int size; int /*<<< orphan*/  options; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  bbt_options; int /*<<< orphan*/  options; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_MAXIMIZE ; 
 int /*<<< orphan*/  NAND_IS_BOOT_MEDIUM ; 
 struct device_node* nand_get_flash_node (struct nand_chip*) ; 
 int of_get_nand_bus_width (struct device_node*) ; 
 int of_get_nand_ecc_algo (struct device_node*) ; 
 int of_get_nand_ecc_mode (struct device_node*) ; 
 int of_get_nand_ecc_step_size (struct device_node*) ; 
 int of_get_nand_ecc_strength (struct device_node*) ; 
 scalar_t__ of_get_nand_on_flash_bbt (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int nand_dt_init(struct nand_chip *chip)
{
	struct device_node *dn = nand_get_flash_node(chip);
	int ecc_mode, ecc_algo, ecc_strength, ecc_step;

	if (!dn)
		return 0;

	if (of_get_nand_bus_width(dn) == 16)
		chip->options |= NAND_BUSWIDTH_16;

	if (of_property_read_bool(dn, "nand-is-boot-medium"))
		chip->options |= NAND_IS_BOOT_MEDIUM;

	if (of_get_nand_on_flash_bbt(dn))
		chip->bbt_options |= NAND_BBT_USE_FLASH;

	ecc_mode = of_get_nand_ecc_mode(dn);
	ecc_algo = of_get_nand_ecc_algo(dn);
	ecc_strength = of_get_nand_ecc_strength(dn);
	ecc_step = of_get_nand_ecc_step_size(dn);

	if (ecc_mode >= 0)
		chip->ecc.mode = ecc_mode;

	if (ecc_algo >= 0)
		chip->ecc.algo = ecc_algo;

	if (ecc_strength >= 0)
		chip->ecc.strength = ecc_strength;

	if (ecc_step > 0)
		chip->ecc.size = ecc_step;

	if (of_property_read_bool(dn, "nand-ecc-maximize"))
		chip->ecc.options |= NAND_ECC_MAXIMIZE;

	return 0;
}