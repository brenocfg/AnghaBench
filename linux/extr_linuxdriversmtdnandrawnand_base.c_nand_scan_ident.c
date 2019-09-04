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
typedef  int u8 ;
struct nand_flash_dev {int dummy; } ;
struct TYPE_4__ {int* data; } ;
struct nand_chip {int options; int numchips; int chipsize; int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;TYPE_2__ id; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  exec_op; } ;
struct TYPE_3__ {scalar_t__ parent; } ;
struct mtd_info {int size; TYPE_1__ dev; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int EINVAL ; 
 int NAND_SCAN_SILENT_NODEV ; 
 int /*<<< orphan*/  NAND_SDR_IFACE ; 
 scalar_t__ dev_name (scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_detect (struct nand_chip*,struct nand_flash_dev*) ; 
 int nand_dt_init (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_readid_op (struct nand_chip*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nand_reset (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_defaults (struct nand_chip*) ; 
 int /*<<< orphan*/  onfi_fill_data_interface (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int) ; 

__attribute__((used)) static int nand_scan_ident(struct mtd_info *mtd, int maxchips,
			   struct nand_flash_dev *table)
{
	int i, nand_maf_id, nand_dev_id;
	struct nand_chip *chip = mtd_to_nand(mtd);
	int ret;

	/* Enforce the right timings for reset/detection */
	onfi_fill_data_interface(chip, NAND_SDR_IFACE, 0);

	ret = nand_dt_init(chip);
	if (ret)
		return ret;

	if (!mtd->name && mtd->dev.parent)
		mtd->name = dev_name(mtd->dev.parent);

	/*
	 * ->cmdfunc() is legacy and will only be used if ->exec_op() is not
	 * populated.
	 */
	if (!chip->exec_op) {
		/*
		 * Default functions assigned for ->cmdfunc() and
		 * ->select_chip() both expect ->cmd_ctrl() to be populated.
		 */
		if ((!chip->cmdfunc || !chip->select_chip) && !chip->cmd_ctrl) {
			pr_err("->cmd_ctrl() should be provided\n");
			return -EINVAL;
		}
	}

	/* Set the default functions */
	nand_set_defaults(chip);

	/* Read the flash type */
	ret = nand_detect(chip, table);
	if (ret) {
		if (!(chip->options & NAND_SCAN_SILENT_NODEV))
			pr_warn("No NAND device found\n");
		chip->select_chip(mtd, -1);
		return ret;
	}

	nand_maf_id = chip->id.data[0];
	nand_dev_id = chip->id.data[1];

	chip->select_chip(mtd, -1);

	/* Check for a chip array */
	for (i = 1; i < maxchips; i++) {
		u8 id[2];

		/* See comment in nand_get_flash_type for reset */
		nand_reset(chip, i);

		chip->select_chip(mtd, i);
		/* Send the command for reading device ID */
		nand_readid_op(chip, 0, id, sizeof(id));
		/* Read manufacturer and device IDs */
		if (nand_maf_id != id[0] || nand_dev_id != id[1]) {
			chip->select_chip(mtd, -1);
			break;
		}
		chip->select_chip(mtd, -1);
	}
	if (i > 1)
		pr_info("%d chips detected\n", i);

	/* Store the number of chips and calc total size for mtd */
	chip->numchips = i;
	mtd->size = i * chip->chipsize;

	return 0;
}