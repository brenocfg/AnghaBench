#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct nand_memory_organization {int pagesize; int pages_per_eraseblock; int /*<<< orphan*/  eraseblocks_per_lun; int /*<<< orphan*/  bits_per_cell; int /*<<< orphan*/  oobsize; } ;
struct nand_flash_dev {int pagesize; int erasesize; int /*<<< orphan*/  name; int /*<<< orphan*/  onfi_timing_mode_default; int /*<<< orphan*/  options; scalar_t__ chipsize; int /*<<< orphan*/  oobsize; int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  model; } ;
struct TYPE_6__ {int /*<<< orphan*/  step_size; int /*<<< orphan*/  strength; } ;
struct TYPE_8__ {TYPE_2__ eccreq; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct nand_chip {TYPE_3__ parameters; int /*<<< orphan*/  onfi_timing_mode_default; TYPE_4__ base; int /*<<< orphan*/  options; TYPE_1__ id; } ;
struct mtd_info {int writesize; int erasesize; int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_DOWN_ULL (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_STEP (struct nand_flash_dev*) ; 
 int /*<<< orphan*/  NAND_ECC_STRENGTH (struct nand_flash_dev*) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_get_bits_per_cell (int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct nand_memory_organization* nanddev_get_memorg (TYPE_4__*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool find_full_id_nand(struct nand_chip *chip,
			      struct nand_flash_dev *type)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_memory_organization *memorg;
	u8 *id_data = chip->id.data;

	memorg = nanddev_get_memorg(&chip->base);

	if (!strncmp(type->id, id_data, type->id_len)) {
		memorg->pagesize = type->pagesize;
		mtd->writesize = memorg->pagesize;
		memorg->pages_per_eraseblock = type->erasesize /
					       type->pagesize;
		mtd->erasesize = type->erasesize;
		memorg->oobsize = type->oobsize;
		mtd->oobsize = memorg->oobsize;

		memorg->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
		memorg->eraseblocks_per_lun =
			DIV_ROUND_DOWN_ULL((u64)type->chipsize << 20,
					   memorg->pagesize *
					   memorg->pages_per_eraseblock);
		chip->options |= type->options;
		chip->base.eccreq.strength = NAND_ECC_STRENGTH(type);
		chip->base.eccreq.step_size = NAND_ECC_STEP(type);
		chip->onfi_timing_mode_default =
					type->onfi_timing_mode_default;

		chip->parameters.model = kstrdup(type->name, GFP_KERNEL);
		if (!chip->parameters.model)
			return false;

		return true;
	}
	return false;
}