#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct spi_controller {int auto_runtime_pm; int mode_bits; int /*<<< orphan*/  slave_abort; int /*<<< orphan*/  setup; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; TYPE_1__ dev; } ;
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mtk_spi_slave {int /*<<< orphan*/  spi_clk; int /*<<< orphan*/  base; TYPE_2__* dev; int /*<<< orphan*/  xfer_done; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_controller*) ; 
 int devm_spi_register_controller (TYPE_2__*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_slave_abort ; 
 int /*<<< orphan*/  mtk_spi_slave_interrupt ; 
 int /*<<< orphan*/  mtk_spi_slave_prepare_message ; 
 int /*<<< orphan*/  mtk_spi_slave_setup ; 
 int /*<<< orphan*/  mtk_spi_slave_transfer_one ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_controller*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 struct spi_controller* spi_alloc_slave (TYPE_2__*,int) ; 
 struct mtk_spi_slave* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 

__attribute__((used)) static int mtk_spi_slave_probe(struct platform_device *pdev)
{
	struct spi_controller *ctlr;
	struct mtk_spi_slave *mdata;
	struct resource *res;
	int irq, ret;

	ctlr = spi_alloc_slave(&pdev->dev, sizeof(*mdata));
	if (!ctlr) {
		dev_err(&pdev->dev, "failed to alloc spi slave\n");
		return -ENOMEM;
	}

	ctlr->auto_runtime_pm = true;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA;
	ctlr->mode_bits |= SPI_LSB_FIRST;

	ctlr->prepare_message = mtk_spi_slave_prepare_message;
	ctlr->transfer_one = mtk_spi_slave_transfer_one;
	ctlr->setup = mtk_spi_slave_setup;
	ctlr->slave_abort = mtk_slave_abort;

	mdata = spi_controller_get_devdata(ctlr);

	platform_set_drvdata(pdev, ctlr);

	init_completion(&mdata->xfer_done);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENODEV;
		dev_err(&pdev->dev, "failed to determine base address\n");
		goto err_put_ctlr;
	}

	mdata->dev = &pdev->dev;

	mdata->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mdata->base)) {
		ret = PTR_ERR(mdata->base);
		goto err_put_ctlr;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_put_ctlr;
	}

	ret = devm_request_irq(&pdev->dev, irq, mtk_spi_slave_interrupt,
			       IRQF_TRIGGER_NONE, dev_name(&pdev->dev), ctlr);
	if (ret) {
		dev_err(&pdev->dev, "failed to register irq (%d)\n", ret);
		goto err_put_ctlr;
	}

	mdata->spi_clk = devm_clk_get(&pdev->dev, "spi");
	if (IS_ERR(mdata->spi_clk)) {
		ret = PTR_ERR(mdata->spi_clk);
		dev_err(&pdev->dev, "failed to get spi-clk: %d\n", ret);
		goto err_put_ctlr;
	}

	ret = clk_prepare_enable(mdata->spi_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable spi_clk (%d)\n", ret);
		goto err_put_ctlr;
	}

	pm_runtime_enable(&pdev->dev);

	ret = devm_spi_register_controller(&pdev->dev, ctlr);
	if (ret) {
		dev_err(&pdev->dev,
			"failed to register slave controller(%d)\n", ret);
		clk_disable_unprepare(mdata->spi_clk);
		goto err_disable_runtime_pm;
	}

	clk_disable_unprepare(mdata->spi_clk);

	return 0;

err_disable_runtime_pm:
	pm_runtime_disable(&pdev->dev);
err_put_ctlr:
	spi_controller_put(ctlr);

	return ret;
}