#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct spi_ops {int /*<<< orphan*/  flags; int /*<<< orphan*/  mode_bits; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_config_register; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct spi_controller {int num_chipselect; int auto_runtime_pm; TYPE_2__ dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode_bits; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  bus_num; } ;
struct rspi_plat_data {int num_chipselect; } ;
struct rspi_data {int rx_irq; int tx_irq; int /*<<< orphan*/  wait; int /*<<< orphan*/  clk; int /*<<< orphan*/  addr; struct spi_controller* ctlr; struct spi_ops const* ops; } ;
struct resource {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; TYPE_1__* id_entry; } ;
struct TYPE_17__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct rspi_plat_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int devm_spi_register_controller (TYPE_3__*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct spi_ops* of_device_get_match_data (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rspi_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  rspi_irq_mux ; 
 int /*<<< orphan*/  rspi_irq_rx ; 
 int /*<<< orphan*/  rspi_irq_tx ; 
 int rspi_parse_dt (TYPE_3__*,struct spi_controller*) ; 
 int /*<<< orphan*/  rspi_prepare_message ; 
 int /*<<< orphan*/  rspi_release_dma (struct spi_controller*) ; 
 int rspi_request_dma (TYPE_3__*,struct spi_controller*,struct resource*) ; 
 int rspi_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,char*,struct rspi_data*) ; 
 int /*<<< orphan*/  rspi_unprepare_message ; 
 struct spi_controller* spi_alloc_master (TYPE_3__*,int) ; 
 struct rspi_data* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 

__attribute__((used)) static int rspi_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct spi_controller *ctlr;
	struct rspi_data *rspi;
	int ret;
	const struct rspi_plat_data *rspi_pd;
	const struct spi_ops *ops;

	ctlr = spi_alloc_master(&pdev->dev, sizeof(struct rspi_data));
	if (ctlr == NULL)
		return -ENOMEM;

	ops = of_device_get_match_data(&pdev->dev);
	if (ops) {
		ret = rspi_parse_dt(&pdev->dev, ctlr);
		if (ret)
			goto error1;
	} else {
		ops = (struct spi_ops *)pdev->id_entry->driver_data;
		rspi_pd = dev_get_platdata(&pdev->dev);
		if (rspi_pd && rspi_pd->num_chipselect)
			ctlr->num_chipselect = rspi_pd->num_chipselect;
		else
			ctlr->num_chipselect = 2; /* default */
	}

	/* ops parameter check */
	if (!ops->set_config_register) {
		dev_err(&pdev->dev, "there is no set_config_register\n");
		ret = -ENODEV;
		goto error1;
	}

	rspi = spi_controller_get_devdata(ctlr);
	platform_set_drvdata(pdev, rspi);
	rspi->ops = ops;
	rspi->ctlr = ctlr;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rspi->addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rspi->addr)) {
		ret = PTR_ERR(rspi->addr);
		goto error1;
	}

	rspi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(rspi->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = PTR_ERR(rspi->clk);
		goto error1;
	}

	pm_runtime_enable(&pdev->dev);

	init_waitqueue_head(&rspi->wait);

	ctlr->bus_num = pdev->id;
	ctlr->auto_runtime_pm = true;
	ctlr->transfer_one = ops->transfer_one;
	ctlr->prepare_message = rspi_prepare_message;
	ctlr->unprepare_message = rspi_unprepare_message;
	ctlr->mode_bits = ops->mode_bits;
	ctlr->flags = ops->flags;
	ctlr->dev.of_node = pdev->dev.of_node;

	ret = platform_get_irq_byname(pdev, "rx");
	if (ret < 0) {
		ret = platform_get_irq_byname(pdev, "mux");
		if (ret < 0)
			ret = platform_get_irq(pdev, 0);
		if (ret >= 0)
			rspi->rx_irq = rspi->tx_irq = ret;
	} else {
		rspi->rx_irq = ret;
		ret = platform_get_irq_byname(pdev, "tx");
		if (ret >= 0)
			rspi->tx_irq = ret;
	}
	if (ret < 0) {
		dev_err(&pdev->dev, "platform_get_irq error\n");
		goto error2;
	}

	if (rspi->rx_irq == rspi->tx_irq) {
		/* Single multiplexed interrupt */
		ret = rspi_request_irq(&pdev->dev, rspi->rx_irq, rspi_irq_mux,
				       "mux", rspi);
	} else {
		/* Multi-interrupt mode, only SPRI and SPTI are used */
		ret = rspi_request_irq(&pdev->dev, rspi->rx_irq, rspi_irq_rx,
				       "rx", rspi);
		if (!ret)
			ret = rspi_request_irq(&pdev->dev, rspi->tx_irq,
					       rspi_irq_tx, "tx", rspi);
	}
	if (ret < 0) {
		dev_err(&pdev->dev, "request_irq error\n");
		goto error2;
	}

	ret = rspi_request_dma(&pdev->dev, ctlr, res);
	if (ret < 0)
		dev_warn(&pdev->dev, "DMA not available, using PIO\n");

	ret = devm_spi_register_controller(&pdev->dev, ctlr);
	if (ret < 0) {
		dev_err(&pdev->dev, "devm_spi_register_controller error.\n");
		goto error3;
	}

	dev_info(&pdev->dev, "probed\n");

	return 0;

error3:
	rspi_release_dma(ctlr);
error2:
	pm_runtime_disable(&pdev->dev);
error1:
	spi_controller_put(ctlr);

	return ret;
}