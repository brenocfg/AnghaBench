#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct spi_controller {int mode_bits; int flags; void* min_speed_hz; void* max_speed_hz; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  can_dma; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; TYPE_1__ dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_12__ {TYPE_2__* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct clk {int dummy; } ;
struct at91_usart_spi {int irq; int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  lock; int /*<<< orphan*/  mpdev; int /*<<< orphan*/  phybase; int /*<<< orphan*/  spi_clk; struct clk* clk; struct clk* regs; TYPE_3__* dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int SPI_MASTER_MUST_RX ; 
 int SPI_MASTER_MUST_TX ; 
 int /*<<< orphan*/  US_MAX_CLK_DIV ; 
 int /*<<< orphan*/  US_MIN_CLK_DIV ; 
 int /*<<< orphan*/  VERSION ; 
 int at91_usart_gpio_setup (struct platform_device*) ; 
 int /*<<< orphan*/  at91_usart_spi_can_dma ; 
 int /*<<< orphan*/  at91_usart_spi_cleanup ; 
 int at91_usart_spi_configure_dma (struct spi_controller*,struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_init (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_interrupt ; 
 int /*<<< orphan*/  at91_usart_spi_prepare_message ; 
 int /*<<< orphan*/  at91_usart_spi_readl (struct at91_usart_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_usart_spi_release_dma (struct spi_controller*) ; 
 int /*<<< orphan*/  at91_usart_spi_setup ; 
 int /*<<< orphan*/  at91_usart_spi_transfer_one ; 
 int /*<<< orphan*/  at91_usart_spi_unprepare_message ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct clk* devm_clk_get (TYPE_2__*,char*) ; 
 struct clk* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_controller*) ; 
 int devm_spi_register_master (TYPE_3__*,struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_controller*) ; 
 struct spi_controller* spi_alloc_master (TYPE_3__*,int) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_controller*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_platform_device (TYPE_2__*) ; 

__attribute__((used)) static int at91_usart_spi_probe(struct platform_device *pdev)
{
	struct resource *regs;
	struct spi_controller *controller;
	struct at91_usart_spi *aus;
	struct clk *clk;
	int irq;
	int ret;

	regs = platform_get_resource(to_platform_device(pdev->dev.parent),
				     IORESOURCE_MEM, 0);
	if (!regs)
		return -EINVAL;

	irq = platform_get_irq(to_platform_device(pdev->dev.parent), 0);
	if (irq < 0)
		return irq;

	clk = devm_clk_get(pdev->dev.parent, "usart");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	ret = -ENOMEM;
	controller = spi_alloc_master(&pdev->dev, sizeof(*aus));
	if (!controller)
		goto at91_usart_spi_probe_fail;

	ret = at91_usart_gpio_setup(pdev);
	if (ret)
		goto at91_usart_spi_probe_fail;

	controller->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP | SPI_CS_HIGH;
	controller->dev.of_node = pdev->dev.parent->of_node;
	controller->bits_per_word_mask = SPI_BPW_MASK(8);
	controller->setup = at91_usart_spi_setup;
	controller->flags = SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX;
	controller->transfer_one = at91_usart_spi_transfer_one;
	controller->prepare_message = at91_usart_spi_prepare_message;
	controller->unprepare_message = at91_usart_spi_unprepare_message;
	controller->can_dma = at91_usart_spi_can_dma;
	controller->cleanup = at91_usart_spi_cleanup;
	controller->max_speed_hz = DIV_ROUND_UP(clk_get_rate(clk),
						US_MIN_CLK_DIV);
	controller->min_speed_hz = DIV_ROUND_UP(clk_get_rate(clk),
						US_MAX_CLK_DIV);
	platform_set_drvdata(pdev, controller);

	aus = spi_master_get_devdata(controller);

	aus->dev = &pdev->dev;
	aus->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(aus->regs)) {
		ret = PTR_ERR(aus->regs);
		goto at91_usart_spi_probe_fail;
	}

	aus->irq = irq;
	aus->clk = clk;

	ret = devm_request_irq(&pdev->dev, irq, at91_usart_spi_interrupt, 0,
			       dev_name(&pdev->dev), controller);
	if (ret)
		goto at91_usart_spi_probe_fail;

	ret = clk_prepare_enable(clk);
	if (ret)
		goto at91_usart_spi_probe_fail;

	aus->spi_clk = clk_get_rate(clk);
	at91_usart_spi_init(aus);

	aus->phybase = regs->start;

	aus->mpdev = to_platform_device(pdev->dev.parent);

	ret = at91_usart_spi_configure_dma(controller, aus);
	if (ret)
		goto at91_usart_fail_dma;

	spin_lock_init(&aus->lock);
	init_completion(&aus->xfer_completion);

	ret = devm_spi_register_master(&pdev->dev, controller);
	if (ret)
		goto at91_usart_fail_register_master;

	dev_info(&pdev->dev,
		 "AT91 USART SPI Controller version 0x%x at %pa (irq %d)\n",
		 at91_usart_spi_readl(aus, VERSION),
		 &regs->start, irq);

	return 0;

at91_usart_fail_register_master:
	at91_usart_spi_release_dma(controller);
at91_usart_fail_dma:
	clk_disable_unprepare(clk);
at91_usart_spi_probe_fail:
	spi_master_put(controller);
	return ret;
}