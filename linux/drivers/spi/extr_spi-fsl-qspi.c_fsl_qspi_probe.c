#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_controller {int mode_bits; int bus_num; int num_chipselect; TYPE_1__ dev; int /*<<< orphan*/ * mem_ops; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct fsl_qspi {int /*<<< orphan*/  lock; void* clk; void* clk_en; int /*<<< orphan*/  memmap_phy; void* ahb_addr; void* iobase; int /*<<< orphan*/  devtype_data; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsl_qspi*) ; 
 int devm_spi_register_controller (struct device*,struct spi_controller*) ; 
 int /*<<< orphan*/  fsl_qspi_clk_disable_unprep (struct fsl_qspi*) ; 
 int fsl_qspi_clk_prep_enable (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_default_setup (struct fsl_qspi*) ; 
 int /*<<< orphan*/  fsl_qspi_irq_handler ; 
 int /*<<< orphan*/  fsl_qspi_mem_ops ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fsl_qspi*) ; 
 struct spi_controller* spi_alloc_master (struct device*,int) ; 
 struct fsl_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 

__attribute__((used)) static int fsl_qspi_probe(struct platform_device *pdev)
{
	struct spi_controller *ctlr;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct resource *res;
	struct fsl_qspi *q;
	int ret;

	ctlr = spi_alloc_master(&pdev->dev, sizeof(*q));
	if (!ctlr)
		return -ENOMEM;

	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD |
			  SPI_TX_DUAL | SPI_TX_QUAD;

	q = spi_controller_get_devdata(ctlr);
	q->dev = dev;
	q->devtype_data = of_device_get_match_data(dev);
	if (!q->devtype_data) {
		ret = -ENODEV;
		goto err_put_ctrl;
	}

	platform_set_drvdata(pdev, q);

	/* find the resources */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "QuadSPI");
	q->iobase = devm_ioremap_resource(dev, res);
	if (IS_ERR(q->iobase)) {
		ret = PTR_ERR(q->iobase);
		goto err_put_ctrl;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					"QuadSPI-memory");
	q->ahb_addr = devm_ioremap_resource(dev, res);
	if (IS_ERR(q->ahb_addr)) {
		ret = PTR_ERR(q->ahb_addr);
		goto err_put_ctrl;
	}

	q->memmap_phy = res->start;

	/* find the clocks */
	q->clk_en = devm_clk_get(dev, "qspi_en");
	if (IS_ERR(q->clk_en)) {
		ret = PTR_ERR(q->clk_en);
		goto err_put_ctrl;
	}

	q->clk = devm_clk_get(dev, "qspi");
	if (IS_ERR(q->clk)) {
		ret = PTR_ERR(q->clk);
		goto err_put_ctrl;
	}

	ret = fsl_qspi_clk_prep_enable(q);
	if (ret) {
		dev_err(dev, "can not enable the clock\n");
		goto err_put_ctrl;
	}

	/* find the irq */
	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto err_disable_clk;

	ret = devm_request_irq(dev, ret,
			fsl_qspi_irq_handler, 0, pdev->name, q);
	if (ret) {
		dev_err(dev, "failed to request irq: %d\n", ret);
		goto err_disable_clk;
	}

	mutex_init(&q->lock);

	ctlr->bus_num = -1;
	ctlr->num_chipselect = 4;
	ctlr->mem_ops = &fsl_qspi_mem_ops;

	fsl_qspi_default_setup(q);

	ctlr->dev.of_node = np;

	ret = devm_spi_register_controller(dev, ctlr);
	if (ret)
		goto err_destroy_mutex;

	return 0;

err_destroy_mutex:
	mutex_destroy(&q->lock);

err_disable_clk:
	fsl_qspi_clk_disable_unprep(q);

err_put_ctrl:
	spi_controller_put(ctlr);

	dev_err(dev, "Freescale QuadSPI probe failed\n");
	return ret;
}