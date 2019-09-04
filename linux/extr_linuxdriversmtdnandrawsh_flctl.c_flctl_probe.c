#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sh_flctl_platform_data {int flcmncr_val; int /*<<< orphan*/  nr_parts; int /*<<< orphan*/  parts; int /*<<< orphan*/  use_holden; scalar_t__ has_hwecc; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; } ;
struct nand_chip {int chip_delay; TYPE_2__ dummy_controller; int /*<<< orphan*/  options; void* get_features; void* set_features; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_word; int /*<<< orphan*/  read_byte; } ;
struct sh_flctl {int flcmncr_base; int flintdmacr_base; scalar_t__ hwecc; int /*<<< orphan*/  holden; struct platform_device* pdev; struct nand_chip chip; scalar_t__ fifo; int /*<<< orphan*/  reg; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_12__ {TYPE_3__* parent; } ;
struct mtd_info {TYPE_1__ dev; } ;

/* Variables and functions */
 int ECERB ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SEL_16BIT ; 
 int STERINTE ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct sh_flctl_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct sh_flctl* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sh_flctl*) ; 
 int /*<<< orphan*/  flctl_cmdfunc ; 
 int /*<<< orphan*/  flctl_handle_flste ; 
 int /*<<< orphan*/  flctl_nand_controller_ops ; 
 struct sh_flctl_platform_data* flctl_parse_dt (TYPE_3__*) ; 
 int /*<<< orphan*/  flctl_read_buf ; 
 int /*<<< orphan*/  flctl_read_byte ; 
 int /*<<< orphan*/  flctl_read_word ; 
 int /*<<< orphan*/  flctl_release_dma (struct sh_flctl*) ; 
 int /*<<< orphan*/  flctl_select_chip ; 
 int /*<<< orphan*/  flctl_setup_dma (struct sh_flctl*) ; 
 int /*<<< orphan*/  flctl_write_buf ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 void* nand_get_set_features_notsupp ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_flctl*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_resume (TYPE_3__*) ; 

__attribute__((used)) static int flctl_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct sh_flctl *flctl;
	struct mtd_info *flctl_mtd;
	struct nand_chip *nand;
	struct sh_flctl_platform_data *pdata;
	int ret;
	int irq;

	flctl = devm_kzalloc(&pdev->dev, sizeof(struct sh_flctl), GFP_KERNEL);
	if (!flctl)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	flctl->reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(flctl->reg))
		return PTR_ERR(flctl->reg);
	flctl->fifo = res->start + 0x24; /* FLDTFIFO */

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "failed to get flste irq data: %d\n", irq);
		return irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, flctl_handle_flste, IRQF_SHARED,
			       "flste", flctl);
	if (ret) {
		dev_err(&pdev->dev, "request interrupt failed.\n");
		return ret;
	}

	if (pdev->dev.of_node)
		pdata = flctl_parse_dt(&pdev->dev);
	else
		pdata = dev_get_platdata(&pdev->dev);

	if (!pdata) {
		dev_err(&pdev->dev, "no setup data defined\n");
		return -EINVAL;
	}

	platform_set_drvdata(pdev, flctl);
	nand = &flctl->chip;
	flctl_mtd = nand_to_mtd(nand);
	nand_set_flash_node(nand, pdev->dev.of_node);
	flctl_mtd->dev.parent = &pdev->dev;
	flctl->pdev = pdev;
	flctl->hwecc = pdata->has_hwecc;
	flctl->holden = pdata->use_holden;
	flctl->flcmncr_base = pdata->flcmncr_val;
	flctl->flintdmacr_base = flctl->hwecc ? (STERINTE | ECERB) : STERINTE;

	/* Set address of hardware control function */
	/* 20 us command delay time */
	nand->chip_delay = 20;

	nand->read_byte = flctl_read_byte;
	nand->read_word = flctl_read_word;
	nand->write_buf = flctl_write_buf;
	nand->read_buf = flctl_read_buf;
	nand->select_chip = flctl_select_chip;
	nand->cmdfunc = flctl_cmdfunc;
	nand->set_features = nand_get_set_features_notsupp;
	nand->get_features = nand_get_set_features_notsupp;

	if (pdata->flcmncr_val & SEL_16BIT)
		nand->options |= NAND_BUSWIDTH_16;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_resume(&pdev->dev);

	flctl_setup_dma(flctl);

	nand->dummy_controller.ops = &flctl_nand_controller_ops;
	ret = nand_scan(flctl_mtd, 1);
	if (ret)
		goto err_chip;

	ret = mtd_device_register(flctl_mtd, pdata->parts, pdata->nr_parts);
	if (ret)
		goto cleanup_nand;

	return 0;

cleanup_nand:
	nand_cleanup(nand);
err_chip:
	flctl_release_dma(flctl);
	pm_runtime_disable(&pdev->dev);
	return ret;
}