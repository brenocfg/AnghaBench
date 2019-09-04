#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int mask; } ;
struct mtd_info {struct spi_nor* priv; } ;
struct spi_nor {int /*<<< orphan*/  erase; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; struct atmel_qspi* priv; TYPE_1__* dev; struct mtd_info mtd; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct atmel_qspi {void* clk; int /*<<< orphan*/  clk_rate; struct spi_nor nor; void* mem; void* regs; struct platform_device* pdev; int /*<<< orphan*/  cmd_completion; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_PP_1_1_4 ; 
 int SNOR_HWCAPS_PP_1_4_4 ; 
 int SNOR_HWCAPS_PP_4_4_4 ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_1_2_2 ; 
 int SNOR_HWCAPS_READ_1_4_4 ; 
 int SNOR_HWCAPS_READ_2_2_2 ; 
 int SNOR_HWCAPS_READ_4_4_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int /*<<< orphan*/  atmel_qspi_erase ; 
 int atmel_qspi_init (struct atmel_qspi*) ; 
 int /*<<< orphan*/  atmel_qspi_interrupt ; 
 int /*<<< orphan*/  atmel_qspi_read ; 
 int /*<<< orphan*/  atmel_qspi_read_reg ; 
 int /*<<< orphan*/  atmel_qspi_write ; 
 int /*<<< orphan*/  atmel_qspi_write_reg ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 void* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct atmel_qspi* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atmel_qspi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_get_child_count (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_qspi*) ; 
 int spi_nor_scan (struct spi_nor*,int /*<<< orphan*/ *,struct spi_nor_hwcaps const*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (struct spi_nor*,struct device_node*) ; 

__attribute__((used)) static int atmel_qspi_probe(struct platform_device *pdev)
{
	const struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_READ_1_1_2 |
			SNOR_HWCAPS_READ_1_2_2 |
			SNOR_HWCAPS_READ_2_2_2 |
			SNOR_HWCAPS_READ_1_1_4 |
			SNOR_HWCAPS_READ_1_4_4 |
			SNOR_HWCAPS_READ_4_4_4 |
			SNOR_HWCAPS_PP |
			SNOR_HWCAPS_PP_1_1_4 |
			SNOR_HWCAPS_PP_1_4_4 |
			SNOR_HWCAPS_PP_4_4_4,
	};
	struct device_node *child, *np = pdev->dev.of_node;
	struct atmel_qspi *aq;
	struct resource *res;
	struct spi_nor *nor;
	struct mtd_info *mtd;
	int irq, err = 0;

	if (of_get_child_count(np) != 1)
		return -ENODEV;
	child = of_get_next_child(np, NULL);

	aq = devm_kzalloc(&pdev->dev, sizeof(*aq), GFP_KERNEL);
	if (!aq) {
		err = -ENOMEM;
		goto exit;
	}

	platform_set_drvdata(pdev, aq);
	init_completion(&aq->cmd_completion);
	aq->pdev = pdev;

	/* Map the registers */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_base");
	aq->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(aq->regs)) {
		dev_err(&pdev->dev, "missing registers\n");
		err = PTR_ERR(aq->regs);
		goto exit;
	}

	/* Map the AHB memory */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_mmap");
	aq->mem = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(aq->mem)) {
		dev_err(&pdev->dev, "missing AHB memory\n");
		err = PTR_ERR(aq->mem);
		goto exit;
	}

	/* Get the peripheral clock */
	aq->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(aq->clk)) {
		dev_err(&pdev->dev, "missing peripheral clock\n");
		err = PTR_ERR(aq->clk);
		goto exit;
	}

	/* Enable the peripheral clock */
	err = clk_prepare_enable(aq->clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable the peripheral clock\n");
		goto exit;
	}

	/* Request the IRQ */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "missing IRQ\n");
		err = irq;
		goto disable_clk;
	}
	err = devm_request_irq(&pdev->dev, irq, atmel_qspi_interrupt,
			       0, dev_name(&pdev->dev), aq);
	if (err)
		goto disable_clk;

	/* Setup the spi-nor */
	nor = &aq->nor;
	mtd = &nor->mtd;

	nor->dev = &pdev->dev;
	spi_nor_set_flash_node(nor, child);
	nor->priv = aq;
	mtd->priv = nor;

	nor->read_reg = atmel_qspi_read_reg;
	nor->write_reg = atmel_qspi_write_reg;
	nor->read = atmel_qspi_read;
	nor->write = atmel_qspi_write;
	nor->erase = atmel_qspi_erase;

	err = of_property_read_u32(child, "spi-max-frequency", &aq->clk_rate);
	if (err < 0)
		goto disable_clk;

	err = atmel_qspi_init(aq);
	if (err)
		goto disable_clk;

	err = spi_nor_scan(nor, NULL, &hwcaps);
	if (err)
		goto disable_clk;

	err = mtd_device_register(mtd, NULL, 0);
	if (err)
		goto disable_clk;

	of_node_put(child);

	return 0;

disable_clk:
	clk_disable_unprepare(aq->clk);
exit:
	of_node_put(child);

	return err;
}