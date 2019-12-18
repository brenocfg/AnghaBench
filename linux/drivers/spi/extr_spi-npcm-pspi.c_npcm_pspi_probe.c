#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct device_node* of_node; } ;
struct spi_master {int mode_bits; int bits_per_word_mask; int num_chipselect; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_transfer_hardware; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  bus_num; TYPE_1__ dev; void* min_speed_hz; void* max_speed_hz; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; } ;
struct npcm_pspi {int is_save_param; int /*<<< orphan*/  clk; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  rst_regmap; int /*<<< orphan*/  base; int /*<<< orphan*/  id; struct spi_master* master; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPCM_PSPI_DEFAULT_CLK ; 
 int /*<<< orphan*/  NPCM_PSPI_MAX_CLK_DIVIDER ; 
 int /*<<< orphan*/  NPCM_PSPI_MIN_CLK_DIVIDER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct npcm_pspi*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npcm_pspi_handler ; 
 int /*<<< orphan*/  npcm_pspi_prepare_transfer_hardware ; 
 int /*<<< orphan*/  npcm_pspi_reset_hw (struct npcm_pspi*) ; 
 int /*<<< orphan*/  npcm_pspi_set_baudrate (struct npcm_pspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npcm_pspi_transfer_one ; 
 int /*<<< orphan*/  npcm_pspi_unprepare_transfer_hardware ; 
 int /*<<< orphan*/  of_alias_get_id (struct device_node*,char*) ; 
 int of_get_named_gpio (struct device_node*,char*,int) ; 
 int of_gpio_named_count (struct device_node*,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct npcm_pspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int npcm_pspi_probe(struct platform_device *pdev)
{
	struct npcm_pspi *priv;
	struct spi_master *master;
	unsigned long clk_hz;
	struct device_node *np = pdev->dev.of_node;
	int num_cs, i;
	int csgpio;
	int irq;
	int ret;

	num_cs = of_gpio_named_count(np, "cs-gpios");
	if (num_cs < 0)
		return num_cs;

	pdev->id = of_alias_get_id(np, "spi");
	if (pdev->id < 0)
		pdev->id = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(*priv));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);

	priv = spi_master_get_devdata(master);
	priv->master = master;
	priv->is_save_param = false;
	priv->id = pdev->id;

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

	priv->rst_regmap =
		syscon_regmap_lookup_by_compatible("nuvoton,npcm750-rst");
	if (IS_ERR(priv->rst_regmap)) {
		dev_err(&pdev->dev, "failed to find nuvoton,npcm750-rst\n");
		return PTR_ERR(priv->rst_regmap);
	}

	/* reset SPI-HW block */
	npcm_pspi_reset_hw(priv);

	ret = devm_request_irq(&pdev->dev, irq, npcm_pspi_handler, 0,
			       "npcm-pspi", priv);
	if (ret) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		goto out_disable_clk;
	}

	init_completion(&priv->xfer_done);

	clk_hz = clk_get_rate(priv->clk);

	master->max_speed_hz = DIV_ROUND_UP(clk_hz, NPCM_PSPI_MIN_CLK_DIVIDER);
	master->min_speed_hz = DIV_ROUND_UP(clk_hz, NPCM_PSPI_MAX_CLK_DIVIDER);
	master->mode_bits = SPI_CPHA | SPI_CPOL;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	master->transfer_one = npcm_pspi_transfer_one;
	master->prepare_transfer_hardware =
		npcm_pspi_prepare_transfer_hardware;
	master->unprepare_transfer_hardware =
		npcm_pspi_unprepare_transfer_hardware;
	master->num_chipselect = num_cs;

	for (i = 0; i < num_cs; i++) {
		csgpio = of_get_named_gpio(np, "cs-gpios", i);
		if (csgpio < 0) {
			dev_err(&pdev->dev, "failed to get csgpio#%u\n", i);
			goto out_disable_clk;
		}
		dev_dbg(&pdev->dev, "csgpio#%u = %d\n", i, csgpio);
		ret = devm_gpio_request_one(&pdev->dev, csgpio,
					    GPIOF_OUT_INIT_HIGH, DRIVER_NAME);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"failed to configure csgpio#%u %d\n"
				, i, csgpio);
			goto out_disable_clk;
		}
	}

	/* set to default clock rate */
	npcm_pspi_set_baudrate(priv, NPCM_PSPI_DEFAULT_CLK);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret)
		goto out_disable_clk;

	pr_info("NPCM Peripheral SPI %d probed\n", pdev->id);

	return 0;

out_disable_clk:
	clk_disable_unprepare(priv->clk);

out_master_put:
	spi_master_put(master);
	return ret;
}