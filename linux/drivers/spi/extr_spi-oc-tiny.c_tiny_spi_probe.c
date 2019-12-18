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
struct tiny_spi_platform_data {unsigned int gpio_cs_count; int /*<<< orphan*/  baudwidth; int /*<<< orphan*/  freq; int /*<<< orphan*/ * gpio_cs; } ;
struct TYPE_2__ {struct spi_master* master; int /*<<< orphan*/  txrx_bufs; int /*<<< orphan*/  chipselect; int /*<<< orphan*/  setup_transfer; } ;
struct tiny_spi {scalar_t__ irq; unsigned int gpio_cs_count; int /*<<< orphan*/ * gpio_cs; int /*<<< orphan*/  base; TYPE_1__ bitbang; int /*<<< orphan*/  baudwidth; int /*<<< orphan*/  freq; int /*<<< orphan*/  done; } ;
struct spi_master {int num_chipselect; int mode_bits; int /*<<< orphan*/  setup; int /*<<< orphan*/  bus_num; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 struct tiny_spi_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tiny_spi*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int max (int,unsigned int) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tiny_spi*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 int spi_bitbang_start (TYPE_1__*) ; 
 struct tiny_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  tiny_spi_chipselect ; 
 int /*<<< orphan*/  tiny_spi_irq ; 
 int tiny_spi_of_probe (struct platform_device*) ; 
 int /*<<< orphan*/  tiny_spi_setup ; 
 int /*<<< orphan*/  tiny_spi_setup_transfer ; 
 int /*<<< orphan*/  tiny_spi_txrx_bufs ; 

__attribute__((used)) static int tiny_spi_probe(struct platform_device *pdev)
{
	struct tiny_spi_platform_data *platp = dev_get_platdata(&pdev->dev);
	struct tiny_spi *hw;
	struct spi_master *master;
	unsigned int i;
	int err = -ENODEV;

	master = spi_alloc_master(&pdev->dev, sizeof(struct tiny_spi));
	if (!master)
		return err;

	/* setup the master state. */
	master->bus_num = pdev->id;
	master->num_chipselect = 255;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->setup = tiny_spi_setup;

	hw = spi_master_get_devdata(master);
	platform_set_drvdata(pdev, hw);

	/* setup the state for the bitbang driver */
	hw->bitbang.master = master;
	hw->bitbang.setup_transfer = tiny_spi_setup_transfer;
	hw->bitbang.chipselect = tiny_spi_chipselect;
	hw->bitbang.txrx_bufs = tiny_spi_txrx_bufs;

	/* find and map our resources */
	hw->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hw->base)) {
		err = PTR_ERR(hw->base);
		goto exit;
	}
	/* irq is optional */
	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq >= 0) {
		init_completion(&hw->done);
		err = devm_request_irq(&pdev->dev, hw->irq, tiny_spi_irq, 0,
				       pdev->name, hw);
		if (err)
			goto exit;
	}
	/* find platform data */
	if (platp) {
		hw->gpio_cs_count = platp->gpio_cs_count;
		hw->gpio_cs = platp->gpio_cs;
		if (platp->gpio_cs_count && !platp->gpio_cs) {
			err = -EBUSY;
			goto exit;
		}
		hw->freq = platp->freq;
		hw->baudwidth = platp->baudwidth;
	} else {
		err = tiny_spi_of_probe(pdev);
		if (err)
			goto exit;
	}
	for (i = 0; i < hw->gpio_cs_count; i++) {
		err = gpio_request(hw->gpio_cs[i], dev_name(&pdev->dev));
		if (err)
			goto exit_gpio;
		gpio_direction_output(hw->gpio_cs[i], 1);
	}
	hw->bitbang.master->num_chipselect = max(1, hw->gpio_cs_count);

	/* register our spi controller */
	err = spi_bitbang_start(&hw->bitbang);
	if (err)
		goto exit;
	dev_info(&pdev->dev, "base %p, irq %d\n", hw->base, hw->irq);

	return 0;

exit_gpio:
	while (i-- > 0)
		gpio_free(hw->gpio_cs[i]);
exit:
	spi_master_put(master);
	return err;
}