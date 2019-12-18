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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_7__ {int chip_delay; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; scalar_t__ IO_ADDR_R; scalar_t__ IO_ADDR_W; } ;
struct nand_chip {int options; TYPE_3__ ecc; int /*<<< orphan*/  bbt_options; TYPE_2__ legacy; TYPE_4__* controller; } ;
struct omap_nand_info {int devsize; int /*<<< orphan*/  dma; scalar_t__ flash_bbt; scalar_t__ ready_gpiod; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  gpmc_cs; struct nand_chip nand; int /*<<< orphan*/  ops; int /*<<< orphan*/  reg; struct platform_device* pdev; } ;
struct TYPE_6__ {struct device* parent; } ;
struct mtd_info {scalar_t__ name; TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 scalar_t__ devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct omap_nand_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_omap_get_nand_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_bch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_controller_init (TYPE_4__*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  omap_dev_ready ; 
 int omap_get_dt_info (struct device*,struct omap_nand_info*) ; 
 TYPE_4__ omap_gpmc_controller ; 
 int omap_gpmc_controller_initialized ; 
 int /*<<< orphan*/  omap_hwcontrol ; 
 int /*<<< orphan*/  omap_nand_controller_ops ; 
 int /*<<< orphan*/  omap_wait ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtd_info*) ; 

__attribute__((used)) static int omap_nand_probe(struct platform_device *pdev)
{
	struct omap_nand_info		*info;
	struct mtd_info			*mtd;
	struct nand_chip		*nand_chip;
	int				err;
	struct resource			*res;
	struct device			*dev = &pdev->dev;

	info = devm_kzalloc(&pdev->dev, sizeof(struct omap_nand_info),
				GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->pdev = pdev;

	err = omap_get_dt_info(dev, info);
	if (err)
		return err;

	info->ops = gpmc_omap_get_nand_ops(&info->reg, info->gpmc_cs);
	if (!info->ops) {
		dev_err(&pdev->dev, "Failed to get GPMC->NAND interface\n");
		return -ENODEV;
	}

	nand_chip		= &info->nand;
	mtd			= nand_to_mtd(nand_chip);
	mtd->dev.parent		= &pdev->dev;
	nand_chip->ecc.priv	= NULL;
	nand_set_flash_node(nand_chip, dev->of_node);

	if (!mtd->name) {
		mtd->name = devm_kasprintf(&pdev->dev, GFP_KERNEL,
					   "omap2-nand.%d", info->gpmc_cs);
		if (!mtd->name) {
			dev_err(&pdev->dev, "Failed to set MTD name\n");
			return -ENOMEM;
		}
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	nand_chip->legacy.IO_ADDR_R = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(nand_chip->legacy.IO_ADDR_R))
		return PTR_ERR(nand_chip->legacy.IO_ADDR_R);

	info->phys_base = res->start;

	if (!omap_gpmc_controller_initialized) {
		omap_gpmc_controller.ops = &omap_nand_controller_ops;
		nand_controller_init(&omap_gpmc_controller);
		omap_gpmc_controller_initialized = true;
	}

	nand_chip->controller = &omap_gpmc_controller;

	nand_chip->legacy.IO_ADDR_W = nand_chip->legacy.IO_ADDR_R;
	nand_chip->legacy.cmd_ctrl  = omap_hwcontrol;

	info->ready_gpiod = devm_gpiod_get_optional(&pdev->dev, "rb",
						    GPIOD_IN);
	if (IS_ERR(info->ready_gpiod)) {
		dev_err(dev, "failed to get ready gpio\n");
		return PTR_ERR(info->ready_gpiod);
	}

	/*
	 * If RDY/BSY line is connected to OMAP then use the omap ready
	 * function and the generic nand_wait function which reads the status
	 * register after monitoring the RDY/BSY line. Otherwise use a standard
	 * chip delay which is slightly more than tR (AC Timing) of the NAND
	 * device and read status register until you get a failure or success
	 */
	if (info->ready_gpiod) {
		nand_chip->legacy.dev_ready = omap_dev_ready;
		nand_chip->legacy.chip_delay = 0;
	} else {
		nand_chip->legacy.waitfunc = omap_wait;
		nand_chip->legacy.chip_delay = 50;
	}

	if (info->flash_bbt)
		nand_chip->bbt_options |= NAND_BBT_USE_FLASH;

	/* scan NAND device connected to chip controller */
	nand_chip->options |= info->devsize & NAND_BUSWIDTH_16;

	err = nand_scan(nand_chip, 1);
	if (err)
		goto return_error;

	err = mtd_device_register(mtd, NULL, 0);
	if (err)
		goto cleanup_nand;

	platform_set_drvdata(pdev, mtd);

	return 0;

cleanup_nand:
	nand_cleanup(nand_chip);

return_error:
	if (!IS_ERR_OR_NULL(info->dma))
		dma_release_channel(info->dma);
	if (nand_chip->ecc.priv) {
		nand_bch_free(nand_chip->ecc.priv);
		nand_chip->ecc.priv = NULL;
	}
	return err;
}