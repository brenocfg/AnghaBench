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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct nand_flash_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  onfi_timing_mode_default; int /*<<< orphan*/  options; scalar_t__ chipsize; int /*<<< orphan*/  oobsize; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  pagesize; int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  model; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct nand_chip {int chipsize; TYPE_2__ parameters; int /*<<< orphan*/  onfi_timing_mode_default; int /*<<< orphan*/  ecc_step_ds; int /*<<< orphan*/  ecc_strength_ds; int /*<<< orphan*/  options; int /*<<< orphan*/  bits_per_cell; TYPE_1__ id; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_STEP (struct nand_flash_dev*) ; 
 int /*<<< orphan*/  NAND_ECC_STRENGTH (struct nand_flash_dev*) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_get_bits_per_cell (int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool find_full_id_nand(struct nand_chip *chip,
			      struct nand_flash_dev *type)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *id_data = chip->id.data;

	if (!strncmp(type->id, id_data, type->id_len)) {
		mtd->writesize = type->pagesize;
		mtd->erasesize = type->erasesize;
		mtd->oobsize = type->oobsize;

		chip->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
		chip->chipsize = (uint64_t)type->chipsize << 20;
		chip->options |= type->options;
		chip->ecc_strength_ds = NAND_ECC_STRENGTH(type);
		chip->ecc_step_ds = NAND_ECC_STEP(type);
		chip->onfi_timing_mode_default =
					type->onfi_timing_mode_default;

		chip->parameters.model = kstrdup(type->name, GFP_KERNEL);
		if (!chip->parameters.model)
			return false;

		return true;
	}
	return false;
}