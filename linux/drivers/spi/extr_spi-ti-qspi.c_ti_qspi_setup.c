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
typedef  int u32 ;
struct ti_qspi_regs {int clkctrl; } ;
struct ti_qspi {int spi_max_frequency; int /*<<< orphan*/  dev; int /*<<< orphan*/  fclk; struct ti_qspi_regs ctx_reg; } ;
struct spi_device {TYPE_1__* master; } ;
struct TYPE_2__ {scalar_t__ busy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int QSPI_CLK_DIV_MAX ; 
 int QSPI_CLK_EN ; 
 int /*<<< orphan*/  QSPI_SPI_CLOCK_CNTRL_REG ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct ti_qspi* spi_master_get_devdata (TYPE_1__*) ; 
 int ti_qspi_read (struct ti_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_qspi_setup(struct spi_device *spi)
{
	struct ti_qspi	*qspi = spi_master_get_devdata(spi->master);
	struct ti_qspi_regs *ctx_reg = &qspi->ctx_reg;
	int clk_div = 0, ret;
	u32 clk_ctrl_reg, clk_rate, clk_mask;

	if (spi->master->busy) {
		dev_dbg(qspi->dev, "master busy doing other transfers\n");
		return -EBUSY;
	}

	if (!qspi->spi_max_frequency) {
		dev_err(qspi->dev, "spi max frequency not defined\n");
		return -EINVAL;
	}

	clk_rate = clk_get_rate(qspi->fclk);

	clk_div = DIV_ROUND_UP(clk_rate, qspi->spi_max_frequency) - 1;

	if (clk_div < 0) {
		dev_dbg(qspi->dev, "clock divider < 0, using /1 divider\n");
		return -EINVAL;
	}

	if (clk_div > QSPI_CLK_DIV_MAX) {
		dev_dbg(qspi->dev, "clock divider >%d , using /%d divider\n",
				QSPI_CLK_DIV_MAX, QSPI_CLK_DIV_MAX + 1);
		return -EINVAL;
	}

	dev_dbg(qspi->dev, "hz: %d, clock divider %d\n",
			qspi->spi_max_frequency, clk_div);

	ret = pm_runtime_get_sync(qspi->dev);
	if (ret < 0) {
		dev_err(qspi->dev, "pm_runtime_get_sync() failed\n");
		return ret;
	}

	clk_ctrl_reg = ti_qspi_read(qspi, QSPI_SPI_CLOCK_CNTRL_REG);

	clk_ctrl_reg &= ~QSPI_CLK_EN;

	/* disable SCLK */
	ti_qspi_write(qspi, clk_ctrl_reg, QSPI_SPI_CLOCK_CNTRL_REG);

	/* enable SCLK */
	clk_mask = QSPI_CLK_EN | clk_div;
	ti_qspi_write(qspi, clk_mask, QSPI_SPI_CLOCK_CNTRL_REG);
	ctx_reg->clkctrl = clk_mask;

	pm_runtime_mark_last_busy(qspi->dev);
	ret = pm_runtime_put_autosuspend(qspi->dev);
	if (ret < 0) {
		dev_err(qspi->dev, "pm_runtime_put_autosuspend() failed\n");
		return ret;
	}

	return 0;
}