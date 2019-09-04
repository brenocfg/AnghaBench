#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct s3c_onenand {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct onenand_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; } ;
struct onenand_chip {int /*<<< orphan*/  subpagesize; int /*<<< orphan*/  options; void* base; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {int /*<<< orphan*/  writesize; scalar_t__ subpage_sft; TYPE_1__ dev; struct onenand_chip* priv; } ;
struct TYPE_7__ {scalar_t__ type; struct platform_device* pdev; int /*<<< orphan*/  complete; void* dma_addr; void* oob_buf; void* page_buf; void* ahb_addr; void* base; int /*<<< orphan*/  phys_base; } ;
struct TYPE_6__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MEM_CFG_OFFSET ; 
 int /*<<< orphan*/  ONENAND_SKIP_UNLOCK_CHECK ; 
 int ONENAND_SYS_CFG1_SYNC_READ ; 
 int PTR_ERR (void*) ; 
 int SZ_4K ; 
 scalar_t__ TYPE_S5PC110 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct onenand_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__**) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* onenand ; 
 int /*<<< orphan*/  onenand_release (struct mtd_info*) ; 
 int onenand_scan (struct mtd_info*,int) ; 
 TYPE_2__* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtd_info*) ; 
 int /*<<< orphan*/  s3c_onenand_setup (struct mtd_info*) ; 
 int s3c_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pc110_dma_irq ; 
 int /*<<< orphan*/  s5pc110_dma_ops ; 
 int /*<<< orphan*/  s5pc110_dma_poll ; 
 int /*<<< orphan*/  s5pc110_onenand_irq ; 

__attribute__((used)) static int s3c_onenand_probe(struct platform_device *pdev)
{
	struct onenand_platform_data *pdata;
	struct onenand_chip *this;
	struct mtd_info *mtd;
	struct resource *r;
	int size, err;

	pdata = dev_get_platdata(&pdev->dev);
	/* No need to check pdata. the platform data is optional */

	size = sizeof(struct mtd_info) + sizeof(struct onenand_chip);
	mtd = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!mtd)
		return -ENOMEM;

	onenand = devm_kzalloc(&pdev->dev, sizeof(struct s3c_onenand),
			       GFP_KERNEL);
	if (!onenand)
		return -ENOMEM;

	this = (struct onenand_chip *) &mtd[1];
	mtd->priv = this;
	mtd->dev.parent = &pdev->dev;
	onenand->pdev = pdev;
	onenand->type = platform_get_device_id(pdev)->driver_data;

	s3c_onenand_setup(mtd);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	onenand->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(onenand->base))
		return PTR_ERR(onenand->base);

	onenand->phys_base = r->start;

	/* Set onenand_chip also */
	this->base = onenand->base;

	/* Use runtime badblock check */
	this->options |= ONENAND_SKIP_UNLOCK_CHECK;

	if (onenand->type != TYPE_S5PC110) {
		r = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		onenand->ahb_addr = devm_ioremap_resource(&pdev->dev, r);
		if (IS_ERR(onenand->ahb_addr))
			return PTR_ERR(onenand->ahb_addr);

		/* Allocate 4KiB BufferRAM */
		onenand->page_buf = devm_kzalloc(&pdev->dev, SZ_4K,
						 GFP_KERNEL);
		if (!onenand->page_buf)
			return -ENOMEM;

		/* Allocate 128 SpareRAM */
		onenand->oob_buf = devm_kzalloc(&pdev->dev, 128, GFP_KERNEL);
		if (!onenand->oob_buf)
			return -ENOMEM;

		/* S3C doesn't handle subpage write */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->writesize;

	} else { /* S5PC110 */
		r = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		onenand->dma_addr = devm_ioremap_resource(&pdev->dev, r);
		if (IS_ERR(onenand->dma_addr))
			return PTR_ERR(onenand->dma_addr);

		s5pc110_dma_ops = s5pc110_dma_poll;
		/* Interrupt support */
		r = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
		if (r) {
			init_completion(&onenand->complete);
			s5pc110_dma_ops = s5pc110_dma_irq;
			err = devm_request_irq(&pdev->dev, r->start,
					       s5pc110_onenand_irq,
					       IRQF_SHARED, "onenand",
					       &onenand);
			if (err) {
				dev_err(&pdev->dev, "failed to get irq\n");
				return err;
			}
		}
	}

	err = onenand_scan(mtd, 1);
	if (err)
		return err;

	if (onenand->type != TYPE_S5PC110) {
		/* S3C doesn't handle subpage write */
		mtd->subpage_sft = 0;
		this->subpagesize = mtd->writesize;
	}

	if (s3c_read_reg(MEM_CFG_OFFSET) & ONENAND_SYS_CFG1_SYNC_READ)
		dev_info(&onenand->pdev->dev, "OneNAND Sync. Burst Read enabled\n");

	err = mtd_device_register(mtd, pdata ? pdata->parts : NULL,
				  pdata ? pdata->nr_parts : 0);
	if (err) {
		dev_err(&pdev->dev, "failed to parse partitions and register the MTD device\n");
		onenand_release(mtd);
		return err;
	}

	platform_set_drvdata(pdev, mtd);

	return 0;
}