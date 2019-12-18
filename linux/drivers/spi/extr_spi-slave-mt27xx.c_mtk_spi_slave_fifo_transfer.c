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
struct spi_transfer {int len; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int dummy; } ;
struct mtk_spi_slave {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPIS_CFG_REG ; 
 int SPIS_RX_EN ; 
 int SPIS_SOFT_RST ; 
 scalar_t__ SPIS_SOFT_RST_REG ; 
 scalar_t__ SPIS_TX_DATA_REG ; 
 int SPIS_TX_EN ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  mtk_spi_slave_disable_xfer (struct mtk_spi_slave*) ; 
 int mtk_spi_slave_wait_for_completion (struct mtk_spi_slave*) ; 
 int readl (scalar_t__) ; 
 struct mtk_spi_slave* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_spi_slave_fifo_transfer(struct spi_controller *ctlr,
				       struct spi_device *spi,
				       struct spi_transfer *xfer)
{
	struct mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	int reg_val, cnt, remainder, ret;

	writel(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);

	reg_val = readl(mdata->base + SPIS_CFG_REG);
	if (xfer->rx_buf)
		reg_val |= SPIS_RX_EN;
	if (xfer->tx_buf)
		reg_val |= SPIS_TX_EN;
	writel(reg_val, mdata->base + SPIS_CFG_REG);

	cnt = xfer->len / 4;
	if (xfer->tx_buf)
		iowrite32_rep(mdata->base + SPIS_TX_DATA_REG,
			      xfer->tx_buf, cnt);

	remainder = xfer->len % 4;
	if (xfer->tx_buf && remainder > 0) {
		reg_val = 0;
		memcpy(&reg_val, xfer->tx_buf + cnt * 4, remainder);
		writel(reg_val, mdata->base + SPIS_TX_DATA_REG);
	}

	ret = mtk_spi_slave_wait_for_completion(mdata);
	if (ret) {
		mtk_spi_slave_disable_xfer(mdata);
		writel(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);
	}

	return ret;
}