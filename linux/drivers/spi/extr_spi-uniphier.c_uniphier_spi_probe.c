#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct uniphier_spi_priv {int is_save_param; int /*<<< orphan*/  clk; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  base; struct spi_master* master; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int num_chipselect; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_transfer_hardware; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  bus_num; TYPE_1__ dev; void* min_speed_hz; void* max_speed_hz; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  SSI_MAX_CLK_DIVIDER ; 
 int /*<<< orphan*/  SSI_MIN_CLK_DIVIDER ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uniphier_spi_priv*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct uniphier_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  uniphier_spi_handler ; 
 int /*<<< orphan*/  uniphier_spi_prepare_transfer_hardware ; 
 int /*<<< orphan*/  uniphier_spi_set_cs ; 
 int /*<<< orphan*/  uniphier_spi_transfer_one ; 
 int /*<<< orphan*/  uniphier_spi_unprepare_transfer_hardware ; 

__attribute__((used)) static int uniphier_spi_probe(struct platform_device *pdev)
{
	struct uniphier_spi_priv *priv;
	struct spi_master *master;
	unsigned long clk_rate;
	int irq;
	int ret;

	master = spi_alloc_master(&pdev->dev, sizeof(*priv));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	priv = spi_master_get_devdata(master);
	priv->master = master;
	priv->is_save_param = false;

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base)) {
		ret = PTR_ERR(priv->base);
		goto out_master_put;
	}

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(priv->clk);
		goto out_master_put;
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		goto out_master_put;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto out_disable_clk;
	}

	ret = devm_request_irq(&pdev->dev, irq, uniphier_spi_handler,
			       0, "uniphier-spi", priv);
	if (ret) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		goto out_disable_clk;
	}

	init_completion(&priv->xfer_done);

	clk_rate = clk_get_rate(priv->clk);

	master->max_speed_hz = DIV_ROUND_UP(clk_rate, SSI_MIN_CLK_DIVIDER);
	master->min_speed_hz = DIV_ROUND_UP(clk_rate, SSI_MAX_CLK_DIVIDER);
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);

	master->set_cs = uniphier_spi_set_cs;
	master->transfer_one = uniphier_spi_transfer_one;
	master->prepare_transfer_hardware
				= uniphier_spi_prepare_transfer_hardware;
	master->unprepare_transfer_hardware
				= uniphier_spi_unprepare_transfer_hardware;
	master->num_chipselect = 1;

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret)
		goto out_disable_clk;

	return 0;

out_disable_clk:
	clk_disable_unprepare(priv->clk);

out_master_put:
	spi_master_put(master);
	return ret;
}