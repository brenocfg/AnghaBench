#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  chip_delay; void* IO_ADDR_R; void* IO_ADDR_W; int /*<<< orphan*/  dev_ready; } ;
struct TYPE_6__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_2__ legacy; int /*<<< orphan*/  options; TYPE_1__ ecc; } ;
struct TYPE_8__ {struct device* parent; } ;
struct mtd_info {int /*<<< orphan*/  size; TYPE_3__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_parts; int /*<<< orphan*/  parts; int /*<<< orphan*/  (* adjust_parts ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  options; } ;
struct gpiomtd {void* nce; void* nwp; TYPE_4__ plat; void* rdy; void* cle; void* ale; void* io_sync; struct nand_chip nand_chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct gpiomtd* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_nand_cmd_ctrl ; 
 int /*<<< orphan*/  gpio_nand_devready ; 
 int gpio_nand_get_config (struct device*,TYPE_4__*) ; 
 struct resource* gpio_nand_get_io_sync (struct platform_device*) ; 
 int /*<<< orphan*/  gpiod_direction_output (void*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (void*,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpiomtd*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_nand_probe(struct platform_device *pdev)
{
	struct gpiomtd *gpiomtd;
	struct nand_chip *chip;
	struct mtd_info *mtd;
	struct resource *res;
	struct device *dev = &pdev->dev;
	int ret = 0;

	if (!dev->of_node && !dev_get_platdata(dev))
		return -EINVAL;

	gpiomtd = devm_kzalloc(dev, sizeof(*gpiomtd), GFP_KERNEL);
	if (!gpiomtd)
		return -ENOMEM;

	chip = &gpiomtd->nand_chip;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->legacy.IO_ADDR_R = devm_ioremap_resource(dev, res);
	if (IS_ERR(chip->legacy.IO_ADDR_R))
		return PTR_ERR(chip->legacy.IO_ADDR_R);

	res = gpio_nand_get_io_sync(pdev);
	if (res) {
		gpiomtd->io_sync = devm_ioremap_resource(dev, res);
		if (IS_ERR(gpiomtd->io_sync))
			return PTR_ERR(gpiomtd->io_sync);
	}

	ret = gpio_nand_get_config(dev, &gpiomtd->plat);
	if (ret)
		return ret;

	/* Just enable the chip */
	gpiomtd->nce = devm_gpiod_get_optional(dev, "nce", GPIOD_OUT_HIGH);
	if (IS_ERR(gpiomtd->nce))
		return PTR_ERR(gpiomtd->nce);

	/* We disable write protection once we know probe() will succeed */
	gpiomtd->nwp = devm_gpiod_get_optional(dev, "nwp", GPIOD_OUT_LOW);
	if (IS_ERR(gpiomtd->nwp)) {
		ret = PTR_ERR(gpiomtd->nwp);
		goto out_ce;
	}

	gpiomtd->ale = devm_gpiod_get(dev, "ale", GPIOD_OUT_LOW);
	if (IS_ERR(gpiomtd->ale)) {
		ret = PTR_ERR(gpiomtd->ale);
		goto out_ce;
	}

	gpiomtd->cle = devm_gpiod_get(dev, "cle", GPIOD_OUT_LOW);
	if (IS_ERR(gpiomtd->cle)) {
		ret = PTR_ERR(gpiomtd->cle);
		goto out_ce;
	}

	gpiomtd->rdy = devm_gpiod_get_optional(dev, "rdy", GPIOD_IN);
	if (IS_ERR(gpiomtd->rdy)) {
		ret = PTR_ERR(gpiomtd->rdy);
		goto out_ce;
	}
	/* Using RDY pin */
	if (gpiomtd->rdy)
		chip->legacy.dev_ready = gpio_nand_devready;

	nand_set_flash_node(chip, pdev->dev.of_node);
	chip->legacy.IO_ADDR_W	= chip->legacy.IO_ADDR_R;
	chip->ecc.mode		= NAND_ECC_SOFT;
	chip->ecc.algo		= NAND_ECC_HAMMING;
	chip->options		= gpiomtd->plat.options;
	chip->legacy.chip_delay	= gpiomtd->plat.chip_delay;
	chip->legacy.cmd_ctrl	= gpio_nand_cmd_ctrl;

	mtd			= nand_to_mtd(chip);
	mtd->dev.parent		= dev;

	platform_set_drvdata(pdev, gpiomtd);

	/* Disable write protection, if wired up */
	if (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_direction_output(gpiomtd->nwp, 1);

	ret = nand_scan(chip, 1);
	if (ret)
		goto err_wp;

	if (gpiomtd->plat.adjust_parts)
		gpiomtd->plat.adjust_parts(&gpiomtd->plat, mtd->size);

	ret = mtd_device_register(mtd, gpiomtd->plat.parts,
				  gpiomtd->plat.num_parts);
	if (!ret)
		return 0;

err_wp:
	if (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_set_value(gpiomtd->nwp, 0);
out_ce:
	if (gpiomtd->nce && !IS_ERR(gpiomtd->nce))
		gpiod_set_value(gpiomtd->nce, 0);

	return ret;
}