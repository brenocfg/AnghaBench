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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; TYPE_2__ ecc; scalar_t__ options; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmdfunc; } ;
struct nuc900_nand {int /*<<< orphan*/  reg; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; struct nand_chip chip; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct nuc900_nand* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nand_scan (struct mtd_info*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nuc900_nand_command_lp ; 
 int /*<<< orphan*/  nuc900_nand_devready ; 
 int /*<<< orphan*/  nuc900_nand_enable (struct nuc900_nand*) ; 
 int /*<<< orphan*/  nuc900_nand_read_buf ; 
 int /*<<< orphan*/  nuc900_nand_read_byte ; 
 int /*<<< orphan*/  nuc900_nand_write_buf ; 
 int /*<<< orphan*/  partitions ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nuc900_nand*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_nand_probe(struct platform_device *pdev)
{
	struct nuc900_nand *nuc900_nand;
	struct nand_chip *chip;
	struct mtd_info *mtd;
	struct resource *res;

	nuc900_nand = devm_kzalloc(&pdev->dev, sizeof(struct nuc900_nand),
				   GFP_KERNEL);
	if (!nuc900_nand)
		return -ENOMEM;
	chip = &(nuc900_nand->chip);
	mtd = nand_to_mtd(chip);

	mtd->dev.parent		= &pdev->dev;
	spin_lock_init(&nuc900_nand->lock);

	nuc900_nand->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(nuc900_nand->clk))
		return -ENOENT;
	clk_enable(nuc900_nand->clk);

	chip->cmdfunc		= nuc900_nand_command_lp;
	chip->dev_ready		= nuc900_nand_devready;
	chip->read_byte		= nuc900_nand_read_byte;
	chip->write_buf		= nuc900_nand_write_buf;
	chip->read_buf		= nuc900_nand_read_buf;
	chip->chip_delay	= 50;
	chip->options		= 0;
	chip->ecc.mode		= NAND_ECC_SOFT;
	chip->ecc.algo		= NAND_ECC_HAMMING;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	nuc900_nand->reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(nuc900_nand->reg))
		return PTR_ERR(nuc900_nand->reg);

	nuc900_nand_enable(nuc900_nand);

	if (nand_scan(mtd, 1))
		return -ENXIO;

	mtd_device_register(mtd, partitions, ARRAY_SIZE(partitions));

	platform_set_drvdata(pdev, nuc900_nand);

	return 0;
}