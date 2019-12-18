#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_15__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_16__ {int chip_delay; TYPE_3__ dummy_controller; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; void* IO_ADDR_W; void* IO_ADDR_R; } ;
struct TYPE_14__ {int strength; int /*<<< orphan*/  hwctl; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  write_oob; int /*<<< orphan*/  write_page; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_4__ legacy; TYPE_2__ ecc; } ;
struct TYPE_13__ {TYPE_6__* parent; } ;
struct mtd_info {char* name; TYPE_1__ dev; int /*<<< orphan*/  owner; } ;
struct lpc32xx_nand_host {int dma_buf_len; int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_chan; TYPE_5__* ncfg; int /*<<< orphan*/ * data_buf; int /*<<< orphan*/  io_base; struct nand_chip nand_chip; int /*<<< orphan*/  pdata; int /*<<< orphan*/  io_base_dma; } ;
struct TYPE_17__ {int wp_gpio; int /*<<< orphan*/  num_parts; int /*<<< orphan*/  parts; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LPC32XX_DMA_DATA_SIZE ; 
 int LPC32XX_ECC_SAVE_SIZE ; 
 int /*<<< orphan*/  NAND_ECC_HW_SYNDROME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* SLC_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_6__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_gpio_request (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  lpc32xx_nand_cmd_ctrl ; 
 int /*<<< orphan*/  lpc32xx_nand_controller_ops ; 
 int /*<<< orphan*/  lpc32xx_nand_device_ready ; 
 int lpc32xx_nand_dma_setup (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_nand_ecc_calculate ; 
 int /*<<< orphan*/  lpc32xx_nand_ecc_enable ; 
 int /*<<< orphan*/  lpc32xx_nand_read_buf ; 
 int /*<<< orphan*/  lpc32xx_nand_read_byte ; 
 int /*<<< orphan*/  lpc32xx_nand_read_oob_syndrome ; 
 int /*<<< orphan*/  lpc32xx_nand_read_page_raw_syndrome ; 
 int /*<<< orphan*/  lpc32xx_nand_read_page_syndrome ; 
 int /*<<< orphan*/  lpc32xx_nand_setup (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_nand_write_buf ; 
 int /*<<< orphan*/  lpc32xx_nand_write_oob_syndrome ; 
 int /*<<< orphan*/  lpc32xx_nand_write_page_raw_syndrome ; 
 int /*<<< orphan*/  lpc32xx_nand_write_page_syndrome ; 
 TYPE_5__* lpc32xx_parse_dt (TYPE_6__*) ; 
 int /*<<< orphan*/  lpc32xx_wp_disable (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  lpc32xx_wp_enable (struct lpc32xx_nand_host*) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_correct_data ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_nand_host*) ; 

__attribute__((used)) static int lpc32xx_nand_probe(struct platform_device *pdev)
{
	struct lpc32xx_nand_host *host;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	struct resource *rc;
	int res;

	/* Allocate memory for the device structure (and zero it) */
	host = devm_kzalloc(&pdev->dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	rc = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, rc);
	if (IS_ERR(host->io_base))
		return PTR_ERR(host->io_base);

	host->io_base_dma = rc->start;
	if (pdev->dev.of_node)
		host->ncfg = lpc32xx_parse_dt(&pdev->dev);
	if (!host->ncfg) {
		dev_err(&pdev->dev,
			"Missing or bad NAND config from device tree\n");
		return -ENOENT;
	}
	if (host->ncfg->wp_gpio == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (gpio_is_valid(host->ncfg->wp_gpio) && devm_gpio_request(&pdev->dev,
			host->ncfg->wp_gpio, "NAND WP")) {
		dev_err(&pdev->dev, "GPIO not available\n");
		return -EBUSY;
	}
	lpc32xx_wp_disable(host);

	host->pdata = dev_get_platdata(&pdev->dev);

	chip = &host->nand_chip;
	mtd = nand_to_mtd(chip);
	nand_set_controller_data(chip, host);
	nand_set_flash_node(chip, pdev->dev.of_node);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &pdev->dev;

	/* Get NAND clock */
	host->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk)) {
		dev_err(&pdev->dev, "Clock failure\n");
		res = -ENOENT;
		goto enable_wp;
	}
	res = clk_prepare_enable(host->clk);
	if (res)
		goto enable_wp;

	/* Set NAND IO addresses and command/ready functions */
	chip->legacy.IO_ADDR_R = SLC_DATA(host->io_base);
	chip->legacy.IO_ADDR_W = SLC_DATA(host->io_base);
	chip->legacy.cmd_ctrl = lpc32xx_nand_cmd_ctrl;
	chip->legacy.dev_ready = lpc32xx_nand_device_ready;
	chip->legacy.chip_delay = 20; /* 20us command delay time */

	/* Init NAND controller */
	lpc32xx_nand_setup(host);

	platform_set_drvdata(pdev, host);

	/* NAND callbacks for LPC32xx SLC hardware */
	chip->ecc.mode = NAND_ECC_HW_SYNDROME;
	chip->legacy.read_byte = lpc32xx_nand_read_byte;
	chip->legacy.read_buf = lpc32xx_nand_read_buf;
	chip->legacy.write_buf = lpc32xx_nand_write_buf;
	chip->ecc.read_page_raw = lpc32xx_nand_read_page_raw_syndrome;
	chip->ecc.read_page = lpc32xx_nand_read_page_syndrome;
	chip->ecc.write_page_raw = lpc32xx_nand_write_page_raw_syndrome;
	chip->ecc.write_page = lpc32xx_nand_write_page_syndrome;
	chip->ecc.write_oob = lpc32xx_nand_write_oob_syndrome;
	chip->ecc.read_oob = lpc32xx_nand_read_oob_syndrome;
	chip->ecc.calculate = lpc32xx_nand_ecc_calculate;
	chip->ecc.correct = nand_correct_data;
	chip->ecc.strength = 1;
	chip->ecc.hwctl = lpc32xx_nand_ecc_enable;

	/*
	 * Allocate a large enough buffer for a single huge page plus
	 * extra space for the spare area and ECC storage area
	 */
	host->dma_buf_len = LPC32XX_DMA_DATA_SIZE + LPC32XX_ECC_SAVE_SIZE;
	host->data_buf = devm_kzalloc(&pdev->dev, host->dma_buf_len,
				      GFP_KERNEL);
	if (host->data_buf == NULL) {
		res = -ENOMEM;
		goto unprepare_clk;
	}

	res = lpc32xx_nand_dma_setup(host);
	if (res) {
		res = -EIO;
		goto unprepare_clk;
	}

	/* Find NAND device */
	chip->legacy.dummy_controller.ops = &lpc32xx_nand_controller_ops;
	res = nand_scan(chip, 1);
	if (res)
		goto release_dma;

	mtd->name = "nxp_lpc3220_slc";
	res = mtd_device_register(mtd, host->ncfg->parts,
				  host->ncfg->num_parts);
	if (res)
		goto cleanup_nand;

	return 0;

cleanup_nand:
	nand_cleanup(chip);
release_dma:
	dma_release_channel(host->dma_chan);
unprepare_clk:
	clk_disable_unprepare(host->clk);
enable_wp:
	lpc32xx_wp_enable(host);

	return res;
}