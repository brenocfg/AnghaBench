#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int num_chipselect; int mode_bits; int bits_per_word_mask; int flags; int min_speed_hz; int max_speed_hz; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  setup; TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct meson_spicc_device {scalar_t__ core; scalar_t__ base; struct platform_device* pdev; struct spi_master* master; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ SPICC_INTREG ; 
 int SPICC_MAX_FREQ ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_MASTER_MUST_RX ; 
 int SPI_MASTER_MUST_TX ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_reset_optional (TYPE_2__*) ; 
 scalar_t__ devm_clk_get (TYPE_2__*,char*) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct meson_spicc_device*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  meson_spicc_cleanup ; 
 int /*<<< orphan*/  meson_spicc_irq ; 
 int /*<<< orphan*/  meson_spicc_prepare_message ; 
 int /*<<< orphan*/  meson_spicc_setup ; 
 int /*<<< orphan*/  meson_spicc_transfer_one ; 
 int /*<<< orphan*/  meson_spicc_unprepare_transfer ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_spicc_device*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct meson_spicc_device* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_spicc_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct meson_spicc_device *spicc;
	int ret, irq, rate;

	master = spi_alloc_master(&pdev->dev, sizeof(*spicc));
	if (!master) {
		dev_err(&pdev->dev, "master allocation failed\n");
		return -ENOMEM;
	}
	spicc = spi_master_get_devdata(master);
	spicc->master = master;

	spicc->pdev = pdev;
	platform_set_drvdata(pdev, spicc);

	spicc->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(spicc->base)) {
		dev_err(&pdev->dev, "io resource mapping failed\n");
		ret = PTR_ERR(spicc->base);
		goto out_master;
	}

	/* Disable all IRQs */
	writel_relaxed(0, spicc->base + SPICC_INTREG);

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, meson_spicc_irq,
			       0, NULL, spicc);
	if (ret) {
		dev_err(&pdev->dev, "irq request failed\n");
		goto out_master;
	}

	spicc->core = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(spicc->core)) {
		dev_err(&pdev->dev, "core clock request failed\n");
		ret = PTR_ERR(spicc->core);
		goto out_master;
	}

	ret = clk_prepare_enable(spicc->core);
	if (ret) {
		dev_err(&pdev->dev, "core clock enable failed\n");
		goto out_master;
	}
	rate = clk_get_rate(spicc->core);

	device_reset_optional(&pdev->dev);

	master->num_chipselect = 4;
	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_MASK(32) |
				     SPI_BPW_MASK(24) |
				     SPI_BPW_MASK(16) |
				     SPI_BPW_MASK(8);
	master->flags = (SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX);
	master->min_speed_hz = rate >> 9;
	master->setup = meson_spicc_setup;
	master->cleanup = meson_spicc_cleanup;
	master->prepare_message = meson_spicc_prepare_message;
	master->unprepare_transfer_hardware = meson_spicc_unprepare_transfer;
	master->transfer_one = meson_spicc_transfer_one;

	/* Setup max rate according to the Meson GX datasheet */
	if ((rate >> 2) > SPICC_MAX_FREQ)
		master->max_speed_hz = SPICC_MAX_FREQ;
	else
		master->max_speed_hz = rate >> 2;

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret) {
		dev_err(&pdev->dev, "spi master registration failed\n");
		goto out_clk;
	}

	return 0;

out_clk:
	clk_disable_unprepare(spicc->core);

out_master:
	spi_master_put(master);

	return ret;
}