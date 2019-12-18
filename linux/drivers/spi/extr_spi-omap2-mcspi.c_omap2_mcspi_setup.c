#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spi_device {size_t chip_select; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  cs_gpio; struct omap2_mcspi_cs* controller_state; int /*<<< orphan*/  master; } ;
struct omap2_mcspi_regs {int /*<<< orphan*/  cs; } ;
struct omap2_mcspi_dma {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;
struct omap2_mcspi_cs {int /*<<< orphan*/  node; scalar_t__ chctrl0; scalar_t__ chconf0; scalar_t__ mode; scalar_t__ phys; scalar_t__ base; } ;
struct omap2_mcspi {int /*<<< orphan*/  dev; scalar_t__ phys; scalar_t__ base; struct omap2_mcspi_dma* dma_channels; struct omap2_mcspi_regs ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap2_mcspi_cs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int omap2_mcspi_request_dma (struct spi_device*) ; 
 int omap2_mcspi_setup_transfer (struct spi_device*,int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 struct omap2_mcspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_mcspi_setup(struct spi_device *spi)
{
	int			ret;
	struct omap2_mcspi	*mcspi = spi_master_get_devdata(spi->master);
	struct omap2_mcspi_regs	*ctx = &mcspi->ctx;
	struct omap2_mcspi_dma	*mcspi_dma;
	struct omap2_mcspi_cs	*cs = spi->controller_state;

	mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	if (!cs) {
		cs = kzalloc(sizeof *cs, GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		cs->base = mcspi->base + spi->chip_select * 0x14;
		cs->phys = mcspi->phys + spi->chip_select * 0x14;
		cs->mode = 0;
		cs->chconf0 = 0;
		cs->chctrl0 = 0;
		spi->controller_state = cs;
		/* Link this to context save list */
		list_add_tail(&cs->node, &ctx->cs);

		if (gpio_is_valid(spi->cs_gpio)) {
			ret = gpio_request(spi->cs_gpio, dev_name(&spi->dev));
			if (ret) {
				dev_err(&spi->dev, "failed to request gpio\n");
				return ret;
			}
			gpio_direction_output(spi->cs_gpio,
					 !(spi->mode & SPI_CS_HIGH));
		}
	}

	if (!mcspi_dma->dma_rx || !mcspi_dma->dma_tx) {
		ret = omap2_mcspi_request_dma(spi);
		if (ret)
			dev_warn(&spi->dev, "not using DMA for McSPI (%d)\n",
				 ret);
	}

	ret = pm_runtime_get_sync(mcspi->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(mcspi->dev);

		return ret;
	}

	ret = omap2_mcspi_setup_transfer(spi, NULL);
	pm_runtime_mark_last_busy(mcspi->dev);
	pm_runtime_put_autosuspend(mcspi->dev);

	return ret;
}