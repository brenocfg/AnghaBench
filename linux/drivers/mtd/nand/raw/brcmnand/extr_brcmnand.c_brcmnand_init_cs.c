#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  write_oob; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  read_oob_raw; int /*<<< orphan*/  write_oob_raw; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  cmd_ctrl; } ;
struct nand_chip {int /*<<< orphan*/ * controller; TYPE_3__ ecc; TYPE_2__ legacy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct brcmnand_host {int /*<<< orphan*/  cs; struct nand_chip chip; struct platform_device* pdev; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CS_CFG ; 
 int CFG_BUS_WIDTH ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  brcmnand_cmd_ctrl ; 
 int /*<<< orphan*/  brcmnand_cmdfunc ; 
 int /*<<< orphan*/  brcmnand_cs_offset (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_read_buf ; 
 int /*<<< orphan*/  brcmnand_read_byte ; 
 int /*<<< orphan*/  brcmnand_read_oob ; 
 int /*<<< orphan*/  brcmnand_read_oob_raw ; 
 int /*<<< orphan*/  brcmnand_read_page ; 
 int /*<<< orphan*/  brcmnand_read_page_raw ; 
 int /*<<< orphan*/  brcmnand_waitfunc ; 
 int /*<<< orphan*/  brcmnand_write_buf ; 
 int /*<<< orphan*/  brcmnand_write_oob ; 
 int /*<<< orphan*/  brcmnand_write_oob_raw ; 
 int /*<<< orphan*/  brcmnand_write_page ; 
 int /*<<< orphan*/  brcmnand_write_page_raw ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_readreg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct brcmnand_host*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_writereg (struct brcmnand_controller*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmnand_init_cs(struct brcmnand_host *host, struct device_node *dn)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	struct platform_device *pdev = host->pdev;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	int ret;
	u16 cfg_offs;

	ret = of_property_read_u32(dn, "reg", &host->cs);
	if (ret) {
		dev_err(&pdev->dev, "can't get chip-select\n");
		return -ENXIO;
	}

	mtd = nand_to_mtd(&host->chip);
	chip = &host->chip;

	nand_set_flash_node(chip, dn);
	nand_set_controller_data(chip, host);
	mtd->name = devm_kasprintf(&pdev->dev, GFP_KERNEL, "brcmnand.%d",
				   host->cs);
	if (!mtd->name)
		return -ENOMEM;

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &pdev->dev;

	chip->legacy.cmd_ctrl = brcmnand_cmd_ctrl;
	chip->legacy.cmdfunc = brcmnand_cmdfunc;
	chip->legacy.waitfunc = brcmnand_waitfunc;
	chip->legacy.read_byte = brcmnand_read_byte;
	chip->legacy.read_buf = brcmnand_read_buf;
	chip->legacy.write_buf = brcmnand_write_buf;

	chip->ecc.mode = NAND_ECC_HW;
	chip->ecc.read_page = brcmnand_read_page;
	chip->ecc.write_page = brcmnand_write_page;
	chip->ecc.read_page_raw = brcmnand_read_page_raw;
	chip->ecc.write_page_raw = brcmnand_write_page_raw;
	chip->ecc.write_oob_raw = brcmnand_write_oob_raw;
	chip->ecc.read_oob_raw = brcmnand_read_oob_raw;
	chip->ecc.read_oob = brcmnand_read_oob;
	chip->ecc.write_oob = brcmnand_write_oob;

	chip->controller = &ctrl->controller;

	/*
	 * The bootloader might have configured 16bit mode but
	 * NAND READID command only works in 8bit mode. We force
	 * 8bit mode here to ensure that NAND READID commands works.
	 */
	cfg_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMNAND_CS_CFG);
	nand_writereg(ctrl, cfg_offs,
		      nand_readreg(ctrl, cfg_offs) & ~CFG_BUS_WIDTH);

	ret = nand_scan(chip, 1);
	if (ret)
		return ret;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret)
		nand_cleanup(chip);

	return ret;
}