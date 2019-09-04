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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u8 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nand_chip {scalar_t__ chipsize; int /*<<< orphan*/  numchips; int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,size_t) ;} ;
struct mtd_info {int /*<<< orphan*/  size; } ;
struct jz_nand {int /*<<< orphan*/ * bank_base; int /*<<< orphan*/ * bank_mem; scalar_t__ base; struct nand_chip chip; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  JZ_NAND_CTRL_ENABLE_CHIP (unsigned char) ; 
 scalar_t__ JZ_REG_NAND_CTRL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int jz_nand_ioremap_resource (struct platform_device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz_nand_iounmap_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_readid_op (struct nand_chip*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  nand_reset_op (struct nand_chip*) ; 
 int nand_scan (struct mtd_info*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,size_t) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,size_t) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int jz_nand_detect_bank(struct platform_device *pdev,
			       struct jz_nand *nand, unsigned char bank,
			       size_t chipnr, uint8_t *nand_maf_id,
			       uint8_t *nand_dev_id)
{
	int ret;
	char res_name[6];
	uint32_t ctrl;
	struct nand_chip *chip = &nand->chip;
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 id[2];

	/* Request I/O resource. */
	sprintf(res_name, "bank%d", bank);
	ret = jz_nand_ioremap_resource(pdev, res_name,
					&nand->bank_mem[bank - 1],
					&nand->bank_base[bank - 1]);
	if (ret)
		return ret;

	/* Enable chip in bank. */
	ctrl = readl(nand->base + JZ_REG_NAND_CTRL);
	ctrl |= JZ_NAND_CTRL_ENABLE_CHIP(bank - 1);
	writel(ctrl, nand->base + JZ_REG_NAND_CTRL);

	if (chipnr == 0) {
		/* Detect first chip. */
		ret = nand_scan(mtd, 1);
		if (ret)
			goto notfound_id;

		/* Retrieve the IDs from the first chip. */
		chip->select_chip(mtd, 0);
		nand_reset_op(chip);
		nand_readid_op(chip, 0, id, sizeof(id));
		*nand_maf_id = id[0];
		*nand_dev_id = id[1];
	} else {
		/* Detect additional chip. */
		chip->select_chip(mtd, chipnr);
		nand_reset_op(chip);
		nand_readid_op(chip, 0, id, sizeof(id));
		if (*nand_maf_id != id[0] || *nand_dev_id != id[1]) {
			ret = -ENODEV;
			goto notfound_id;
		}

		/* Update size of the MTD. */
		chip->numchips++;
		mtd->size += chip->chipsize;
	}

	dev_info(&pdev->dev, "Found chip %zu on bank %i\n", chipnr, bank);
	return 0;

notfound_id:
	dev_info(&pdev->dev, "No chip found on bank %i\n", bank);
	ctrl &= ~(JZ_NAND_CTRL_ENABLE_CHIP(bank - 1));
	writel(ctrl, nand->base + JZ_REG_NAND_CTRL);
	jz_nand_iounmap_resource(nand->bank_mem[bank - 1],
				 nand->bank_base[bank - 1]);
	return ret;
}