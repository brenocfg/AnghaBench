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
struct stm32_qspi {scalar_t__ mm_size; int /*<<< orphan*/  lock; struct device* dev; struct reset_control* clk; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  data_completion; struct reset_control* mm_base; int /*<<< orphan*/  phys_base; struct reset_control* io_base; struct spi_controller* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct spi_controller {int mode_bits; int bus_num; TYPE_1__ dev; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/  setup; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct reset_control {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 scalar_t__ STM32_QSPI_MAX_MMAP_SZ ; 
 int /*<<< orphan*/  STM32_QSPI_MAX_NORCHIP ; 
 int /*<<< orphan*/  clk_get_rate (struct reset_control*) ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct reset_control* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_qspi*) ; 
 struct reset_control* devm_reset_control_get_exclusive (struct device*,int /*<<< orphan*/ *) ; 
 int devm_spi_register_master (struct device*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_qspi*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 scalar_t__ resource_size (struct resource*) ; 
 struct spi_controller* spi_alloc_master (struct device*,int) ; 
 struct stm32_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  stm32_qspi_dma_setup (struct stm32_qspi*) ; 
 int /*<<< orphan*/  stm32_qspi_irq ; 
 int /*<<< orphan*/  stm32_qspi_mem_ops ; 
 int /*<<< orphan*/  stm32_qspi_release (struct stm32_qspi*) ; 
 int /*<<< orphan*/  stm32_qspi_setup ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_qspi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct spi_controller *ctrl;
	struct reset_control *rstc;
	struct stm32_qspi *qspi;
	struct resource *res;
	int ret, irq;

	ctrl = spi_alloc_master(dev, sizeof(*qspi));
	if (!ctrl)
		return -ENOMEM;

	qspi = spi_controller_get_devdata(ctrl);
	qspi->ctrl = ctrl;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qspi");
	qspi->io_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(qspi->io_base)) {
		ret = PTR_ERR(qspi->io_base);
		goto err;
	}

	qspi->phys_base = res->start;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_mm");
	qspi->mm_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(qspi->mm_base)) {
		ret = PTR_ERR(qspi->mm_base);
		goto err;
	}

	qspi->mm_size = resource_size(res);
	if (qspi->mm_size > STM32_QSPI_MAX_MMAP_SZ) {
		ret = -EINVAL;
		goto err;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(dev, irq, stm32_qspi_irq, 0,
			       dev_name(dev), qspi);
	if (ret) {
		dev_err(dev, "failed to request irq\n");
		goto err;
	}

	init_completion(&qspi->data_completion);

	qspi->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(qspi->clk)) {
		ret = PTR_ERR(qspi->clk);
		goto err;
	}

	qspi->clk_rate = clk_get_rate(qspi->clk);
	if (!qspi->clk_rate) {
		ret = -EINVAL;
		goto err;
	}

	ret = clk_prepare_enable(qspi->clk);
	if (ret) {
		dev_err(dev, "can not enable the clock\n");
		goto err;
	}

	rstc = devm_reset_control_get_exclusive(dev, NULL);
	if (!IS_ERR(rstc)) {
		reset_control_assert(rstc);
		udelay(2);
		reset_control_deassert(rstc);
	}

	qspi->dev = dev;
	platform_set_drvdata(pdev, qspi);
	stm32_qspi_dma_setup(qspi);
	mutex_init(&qspi->lock);

	ctrl->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD
		| SPI_TX_DUAL | SPI_TX_QUAD;
	ctrl->setup = stm32_qspi_setup;
	ctrl->bus_num = -1;
	ctrl->mem_ops = &stm32_qspi_mem_ops;
	ctrl->num_chipselect = STM32_QSPI_MAX_NORCHIP;
	ctrl->dev.of_node = dev->of_node;

	ret = devm_spi_register_master(dev, ctrl);
	if (!ret)
		return 0;

err:
	stm32_qspi_release(qspi);
	return ret;
}