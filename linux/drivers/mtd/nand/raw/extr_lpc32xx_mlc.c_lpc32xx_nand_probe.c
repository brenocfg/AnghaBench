#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_15__ {int chip_delay; TYPE_3__ dummy_controller; int /*<<< orphan*/  waitfunc; void* IO_ADDR_W; void* IO_ADDR_R; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; } ;
struct TYPE_13__ {int strength; int bytes; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  write_oob; void* write_page; void* write_page_raw; void* read_page; void* read_page_raw; int /*<<< orphan*/  hwctl; } ;
struct nand_chip {int bbt_options; TYPE_4__ legacy; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; int /*<<< orphan*/  options; TYPE_2__ ecc; } ;
struct TYPE_12__ {TYPE_6__* parent; } ;
struct mtd_info {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct lpc32xx_nand_host {scalar_t__ irq; TYPE_5__* ncfg; int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  comp_controller; int /*<<< orphan*/  comp_nand; int /*<<< orphan*/  io_base; int /*<<< orphan*/  pdata; struct nand_chip nand_chip; int /*<<< orphan*/  io_base_phy; struct platform_device* pdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_16__ {int wp_gpio; int /*<<< orphan*/  num_parts; int /*<<< orphan*/  parts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* MLC_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_IRQ_SR (int /*<<< orphan*/ ) ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_6__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 struct lpc32xx_nand_host* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 scalar_t__ gpio_request (int,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int lpc32xx_dma_setup (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_ecc_enable ; 
 int /*<<< orphan*/  lpc32xx_nand_bbt ; 
 int /*<<< orphan*/  lpc32xx_nand_bbt_mirror ; 
 int /*<<< orphan*/  lpc32xx_nand_cmd_ctrl ; 
 int /*<<< orphan*/  lpc32xx_nand_controller_ops ; 
 int /*<<< orphan*/  lpc32xx_nand_device_ready ; 
 int /*<<< orphan*/  lpc32xx_nand_setup (struct lpc32xx_nand_host*) ; 
 TYPE_5__* lpc32xx_parse_dt (TYPE_6__*) ; 
 int /*<<< orphan*/  lpc32xx_read_oob ; 
 void* lpc32xx_read_page ; 
 int /*<<< orphan*/  lpc32xx_waitfunc ; 
 int /*<<< orphan*/  lpc32xx_wp_disable (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_wp_enable (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_write_oob ; 
 void* lpc32xx_write_page_lowlevel ; 
 int /*<<< orphan*/  lpc3xxx_nand_irq ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc32xx_nand_host*) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static int lpc32xx_nand_probe(struct platform_device *pdev)
{
	struct lpc32xx_nand_host *host;
	struct mtd_info *mtd;
	struct nand_chip *nand_chip;
	struct resource *rc;
	int res;

	/* Allocate memory for the device structure (and zero it) */
	host = devm_kzalloc(&pdev->dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	host->pdev = pdev;

	rc = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, rc);
	if (IS_ERR(host->io_base))
		return PTR_ERR(host->io_base);

	host->io_base_phy = rc->start;

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	if (pdev->dev.of_node)
		host->ncfg = lpc32xx_parse_dt(&pdev->dev);
	if (!host->ncfg) {
		dev_err(&pdev->dev,
			"Missing or bad NAND config from device tree\n");
		return -ENOENT;
	}
	if (host->ncfg->wp_gpio == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (gpio_is_valid(host->ncfg->wp_gpio) &&
			gpio_request(host->ncfg->wp_gpio, "NAND WP")) {
		dev_err(&pdev->dev, "GPIO not available\n");
		return -EBUSY;
	}
	lpc32xx_wp_disable(host);

	host->pdata = dev_get_platdata(&pdev->dev);

	/* link the private data structures */
	nand_set_controller_data(nand_chip, host);
	nand_set_flash_node(nand_chip, pdev->dev.of_node);
	mtd->dev.parent = &pdev->dev;

	/* Get NAND clock */
	host->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk)) {
		dev_err(&pdev->dev, "Clock initialization failure\n");
		res = -ENOENT;
		goto free_gpio;
	}
	res = clk_prepare_enable(host->clk);
	if (res)
		goto put_clk;

	nand_chip->legacy.cmd_ctrl = lpc32xx_nand_cmd_ctrl;
	nand_chip->legacy.dev_ready = lpc32xx_nand_device_ready;
	nand_chip->legacy.chip_delay = 25; /* us */
	nand_chip->legacy.IO_ADDR_R = MLC_DATA(host->io_base);
	nand_chip->legacy.IO_ADDR_W = MLC_DATA(host->io_base);

	/* Init NAND controller */
	lpc32xx_nand_setup(host);

	platform_set_drvdata(pdev, host);

	/* Initialize function pointers */
	nand_chip->ecc.hwctl = lpc32xx_ecc_enable;
	nand_chip->ecc.read_page_raw = lpc32xx_read_page;
	nand_chip->ecc.read_page = lpc32xx_read_page;
	nand_chip->ecc.write_page_raw = lpc32xx_write_page_lowlevel;
	nand_chip->ecc.write_page = lpc32xx_write_page_lowlevel;
	nand_chip->ecc.write_oob = lpc32xx_write_oob;
	nand_chip->ecc.read_oob = lpc32xx_read_oob;
	nand_chip->ecc.strength = 4;
	nand_chip->ecc.bytes = 10;
	nand_chip->legacy.waitfunc = lpc32xx_waitfunc;

	nand_chip->options = NAND_NO_SUBPAGE_WRITE;
	nand_chip->bbt_options = NAND_BBT_USE_FLASH | NAND_BBT_NO_OOB;
	nand_chip->bbt_td = &lpc32xx_nand_bbt;
	nand_chip->bbt_md = &lpc32xx_nand_bbt_mirror;

	if (use_dma) {
		res = lpc32xx_dma_setup(host);
		if (res) {
			res = -EIO;
			goto unprepare_clk;
		}
	}

	/* initially clear interrupt status */
	readb(MLC_IRQ_SR(host->io_base));

	init_completion(&host->comp_nand);
	init_completion(&host->comp_controller);

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq < 0) {
		dev_err(&pdev->dev, "failed to get platform irq\n");
		res = -EINVAL;
		goto release_dma_chan;
	}

	if (request_irq(host->irq, (irq_handler_t)&lpc3xxx_nand_irq,
			IRQF_TRIGGER_HIGH, DRV_NAME, host)) {
		dev_err(&pdev->dev, "Error requesting NAND IRQ\n");
		res = -ENXIO;
		goto release_dma_chan;
	}

	/*
	 * Scan to find existence of the device and get the type of NAND device:
	 * SMALL block or LARGE block.
	 */
	nand_chip->legacy.dummy_controller.ops = &lpc32xx_nand_controller_ops;
	res = nand_scan(nand_chip, 1);
	if (res)
		goto free_irq;

	mtd->name = DRV_NAME;

	res = mtd_device_register(mtd, host->ncfg->parts,
				  host->ncfg->num_parts);
	if (res)
		goto cleanup_nand;

	return 0;

cleanup_nand:
	nand_cleanup(nand_chip);
free_irq:
	free_irq(host->irq, host);
release_dma_chan:
	if (use_dma)
		dma_release_channel(host->dma_chan);
unprepare_clk:
	clk_disable_unprepare(host->clk);
put_clk:
	clk_put(host->clk);
free_gpio:
	lpc32xx_wp_enable(host);
	gpio_free(host->ncfg->wp_gpio);

	return res;
}