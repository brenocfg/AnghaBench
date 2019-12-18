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
struct spi_master {int mode_bits; int num_chipselect; TYPE_1__ dev; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct bcm2835aux_spi {int irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_NO_CS ; 
 int /*<<< orphan*/  bcm2835aux_debugfs_create (struct bcm2835aux_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835aux_spi_handle_err ; 
 int /*<<< orphan*/  bcm2835aux_spi_interrupt ; 
 int /*<<< orphan*/  bcm2835aux_spi_prepare_message ; 
 int /*<<< orphan*/  bcm2835aux_spi_reset_hw (struct bcm2835aux_spi*) ; 
 int /*<<< orphan*/  bcm2835aux_spi_setup ; 
 int /*<<< orphan*/  bcm2835aux_spi_transfer_one ; 
 int /*<<< orphan*/  bcm2835aux_spi_unprepare_message ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int bcm2835aux_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct bcm2835aux_spi *bs;
	unsigned long clk_hz;
	int err;

	master = spi_alloc_master(&pdev->dev, sizeof(*bs));
	if (!master)
		return -ENOMEM;

	platform_set_drvdata(pdev, master);
	master->mode_bits = (SPI_CPOL | SPI_CS_HIGH | SPI_NO_CS);
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	/* even though the driver never officially supported native CS
	 * allow a single native CS for legacy DT support purposes when
	 * no cs-gpio is configured.
	 * Known limitations for native cs are:
	 * * multiple chip-selects: cs0-cs2 are all simultaniously asserted
	 *     whenever there is a transfer -  this even includes SPI_NO_CS
	 * * SPI_CS_HIGH: is ignores - cs are always asserted low
	 * * cs_change: cs is deasserted after each spi_transfer
	 * * cs_delay_usec: cs is always deasserted one SCK cycle after
	 *     a spi_transfer
	 */
	master->num_chipselect = 1;
	master->setup = bcm2835aux_spi_setup;
	master->transfer_one = bcm2835aux_spi_transfer_one;
	master->handle_err = bcm2835aux_spi_handle_err;
	master->prepare_message = bcm2835aux_spi_prepare_message;
	master->unprepare_message = bcm2835aux_spi_unprepare_message;
	master->dev.of_node = pdev->dev.of_node;

	bs = spi_master_get_devdata(master);

	/* the main area */
	bs->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(bs->regs)) {
		err = PTR_ERR(bs->regs);
		goto out_master_put;
	}

	bs->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(bs->clk)) {
		err = PTR_ERR(bs->clk);
		dev_err(&pdev->dev, "could not get clk: %d\n", err);
		goto out_master_put;
	}

	bs->irq = platform_get_irq(pdev, 0);
	if (bs->irq <= 0) {
		err = bs->irq ? bs->irq : -ENODEV;
		goto out_master_put;
	}

	/* this also enables the HW block */
	err = clk_prepare_enable(bs->clk);
	if (err) {
		dev_err(&pdev->dev, "could not prepare clock: %d\n", err);
		goto out_master_put;
	}

	/* just checking if the clock returns a sane value */
	clk_hz = clk_get_rate(bs->clk);
	if (!clk_hz) {
		dev_err(&pdev->dev, "clock returns 0 Hz\n");
		err = -ENODEV;
		goto out_clk_disable;
	}

	/* reset SPI-HW block */
	bcm2835aux_spi_reset_hw(bs);

	err = devm_request_irq(&pdev->dev, bs->irq,
			       bcm2835aux_spi_interrupt,
			       IRQF_SHARED,
			       dev_name(&pdev->dev), master);
	if (err) {
		dev_err(&pdev->dev, "could not request IRQ: %d\n", err);
		goto out_clk_disable;
	}

	err = devm_spi_register_master(&pdev->dev, master);
	if (err) {
		dev_err(&pdev->dev, "could not register SPI master: %d\n", err);
		goto out_clk_disable;
	}

	bcm2835aux_debugfs_create(bs, dev_name(&pdev->dev));

	return 0;

out_clk_disable:
	clk_disable_unprepare(bs->clk);
out_master_put:
	spi_master_put(master);
	return err;
}