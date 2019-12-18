#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcan4x5x_priv {int /*<<< orphan*/  power; int /*<<< orphan*/  regmap; struct m_can_classdev* mcan_dev; struct spi_device* spi; int /*<<< orphan*/  mram_start; int /*<<< orphan*/  reg_offset; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int freq; } ;
struct TYPE_5__ {TYPE_1__ clock; } ;
struct m_can_classdev {int is_peripheral; int /*<<< orphan*/  hclk; int /*<<< orphan*/  cclk; TYPE_3__* net; int /*<<< orphan*/ * data_timing; int /*<<< orphan*/ * bit_timing; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; TYPE_2__ can; scalar_t__ pm_clock_support; struct tcan4x5x_priv* device_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int TCAN4X5X_EXT_CLK_DEF ; 
 int /*<<< orphan*/  TCAN4X5X_MCAN_OFFSET ; 
 int /*<<< orphan*/  TCAN4X5X_MRAM_START ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct tcan4x5x_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct m_can_classdev* m_can_class_allocate_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_can_class_get_clocks (struct m_can_classdev*) ; 
 int m_can_class_register (struct m_can_classdev*) ; 
 int /*<<< orphan*/  netdev_info (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tcan4x5x_priv*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  tcan4x5x_bittiming_const ; 
 int /*<<< orphan*/  tcan4x5x_bus ; 
 int /*<<< orphan*/  tcan4x5x_data_bittiming_const ; 
 int /*<<< orphan*/  tcan4x5x_ops ; 
 int tcan4x5x_parse_config (struct m_can_classdev*) ; 
 int /*<<< orphan*/  tcan4x5x_power_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcan4x5x_regmap ; 

__attribute__((used)) static int tcan4x5x_can_probe(struct spi_device *spi)
{
	struct tcan4x5x_priv *priv;
	struct m_can_classdev *mcan_class;
	int freq, ret;

	mcan_class = m_can_class_allocate_dev(&spi->dev);
	if (!mcan_class)
		return -ENOMEM;

	priv = devm_kzalloc(&spi->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mcan_class->device_data = priv;

	m_can_class_get_clocks(mcan_class);
	if (IS_ERR(mcan_class->cclk)) {
		dev_err(&spi->dev, "no CAN clock source defined\n");
		freq = TCAN4X5X_EXT_CLK_DEF;
	} else {
		freq = clk_get_rate(mcan_class->cclk);
	}

	/* Sanity check */
	if (freq < 20000000 || freq > TCAN4X5X_EXT_CLK_DEF)
		return -ERANGE;

	priv->reg_offset = TCAN4X5X_MCAN_OFFSET;
	priv->mram_start = TCAN4X5X_MRAM_START;
	priv->spi = spi;
	priv->mcan_dev = mcan_class;

	mcan_class->pm_clock_support = 0;
	mcan_class->can.clock.freq = freq;
	mcan_class->dev = &spi->dev;
	mcan_class->ops = &tcan4x5x_ops;
	mcan_class->is_peripheral = true;
	mcan_class->bit_timing = &tcan4x5x_bittiming_const;
	mcan_class->data_timing = &tcan4x5x_data_bittiming_const;
	mcan_class->net->irq = spi->irq;

	spi_set_drvdata(spi, priv);

	ret = tcan4x5x_parse_config(mcan_class);
	if (ret)
		goto out_clk;

	/* Configure the SPI bus */
	spi->bits_per_word = 32;
	ret = spi_setup(spi);
	if (ret)
		goto out_clk;

	priv->regmap = devm_regmap_init(&spi->dev, &tcan4x5x_bus,
					&spi->dev, &tcan4x5x_regmap);

	tcan4x5x_power_enable(priv->power, 1);

	ret = m_can_class_register(mcan_class);
	if (ret)
		goto out_power;

	netdev_info(mcan_class->net, "TCAN4X5X successfully initialized.\n");
	return 0;

out_power:
	tcan4x5x_power_enable(priv->power, 0);
out_clk:
	if (!IS_ERR(mcan_class->cclk)) {
		clk_disable_unprepare(mcan_class->cclk);
		clk_disable_unprepare(mcan_class->hclk);
	}

	dev_err(&spi->dev, "Probe failed, err=%d\n", ret);
	return ret;
}