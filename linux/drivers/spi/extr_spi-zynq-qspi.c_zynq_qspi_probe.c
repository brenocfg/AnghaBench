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
typedef  int /*<<< orphan*/  u32 ;
struct zynq_qspi {scalar_t__ irq; void* pclk; void* refclk; int /*<<< orphan*/  data_completion; void* regs; struct device* dev; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_controller {int mode_bits; int max_speed_hz; TYPE_1__ dev; int /*<<< orphan*/  setup; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/  num_chipselect; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  ZYNQ_QSPI_DEFAULT_NUM_CS ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zynq_qspi*) ; 
 int devm_spi_register_controller (struct device*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynq_qspi*) ; 
 struct spi_controller* spi_alloc_master (struct device*,int) ; 
 struct zynq_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 
 int /*<<< orphan*/  zynq_qspi_init_hw (struct zynq_qspi*) ; 
 int /*<<< orphan*/  zynq_qspi_irq ; 
 int /*<<< orphan*/  zynq_qspi_mem_ops ; 
 int /*<<< orphan*/  zynq_qspi_setup_op ; 

__attribute__((used)) static int zynq_qspi_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct spi_controller *ctlr;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct zynq_qspi *xqspi;
	u32 num_cs;

	ctlr = spi_alloc_master(&pdev->dev, sizeof(*xqspi));
	if (!ctlr)
		return -ENOMEM;

	xqspi = spi_controller_get_devdata(ctlr);
	xqspi->dev = dev;
	platform_set_drvdata(pdev, xqspi);
	xqspi->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(xqspi->regs)) {
		ret = PTR_ERR(xqspi->regs);
		goto remove_master;
	}

	xqspi->pclk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(xqspi->pclk)) {
		dev_err(&pdev->dev, "pclk clock not found.\n");
		ret = PTR_ERR(xqspi->pclk);
		goto remove_master;
	}

	init_completion(&xqspi->data_completion);

	xqspi->refclk = devm_clk_get(&pdev->dev, "ref_clk");
	if (IS_ERR(xqspi->refclk)) {
		dev_err(&pdev->dev, "ref_clk clock not found.\n");
		ret = PTR_ERR(xqspi->refclk);
		goto remove_master;
	}

	ret = clk_prepare_enable(xqspi->pclk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable APB clock.\n");
		goto remove_master;
	}

	ret = clk_prepare_enable(xqspi->refclk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable device clock.\n");
		goto clk_dis_pclk;
	}

	/* QSPI controller initializations */
	zynq_qspi_init_hw(xqspi);

	xqspi->irq = platform_get_irq(pdev, 0);
	if (xqspi->irq <= 0) {
		ret = -ENXIO;
		goto remove_master;
	}
	ret = devm_request_irq(&pdev->dev, xqspi->irq, zynq_qspi_irq,
			       0, pdev->name, xqspi);
	if (ret != 0) {
		ret = -ENXIO;
		dev_err(&pdev->dev, "request_irq failed\n");
		goto remove_master;
	}

	ret = of_property_read_u32(np, "num-cs",
				   &num_cs);
	if (ret < 0)
		ctlr->num_chipselect = ZYNQ_QSPI_DEFAULT_NUM_CS;
	else
		ctlr->num_chipselect = num_cs;

	ctlr->mode_bits =  SPI_RX_DUAL | SPI_RX_QUAD |
			    SPI_TX_DUAL | SPI_TX_QUAD;
	ctlr->mem_ops = &zynq_qspi_mem_ops;
	ctlr->setup = zynq_qspi_setup_op;
	ctlr->max_speed_hz = clk_get_rate(xqspi->refclk) / 2;
	ctlr->dev.of_node = np;
	ret = devm_spi_register_controller(&pdev->dev, ctlr);
	if (ret) {
		dev_err(&pdev->dev, "spi_register_master failed\n");
		goto clk_dis_all;
	}

	return ret;

clk_dis_all:
	clk_disable_unprepare(xqspi->refclk);
clk_dis_pclk:
	clk_disable_unprepare(xqspi->pclk);
remove_master:
	spi_controller_put(ctlr);

	return ret;
}