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
typedef  scalar_t__ u32 ;
struct spi_transfer {int len; scalar_t__ tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct mtk_spi {scalar_t__ base; scalar_t__ num_xfered; int /*<<< orphan*/  xfer_len; struct spi_transfer* cur_transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_SPI_MAX_FIFO_SIZE ; 
 scalar_t__ SPI_TX_DATA_REG ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_spi_enable_transfer (struct spi_master*) ; 
 int /*<<< orphan*/  mtk_spi_prepare_transfer (struct spi_master*,struct spi_transfer*) ; 
 int /*<<< orphan*/  mtk_spi_setup_packet (struct spi_master*) ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mtk_spi_fifo_transfer(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	int cnt, remainder;
	u32 reg_val;
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	mdata->cur_transfer = xfer;
	mdata->xfer_len = min(MTK_SPI_MAX_FIFO_SIZE, xfer->len);
	mdata->num_xfered = 0;
	mtk_spi_prepare_transfer(master, xfer);
	mtk_spi_setup_packet(master);

	cnt = xfer->len / 4;
	iowrite32_rep(mdata->base + SPI_TX_DATA_REG, xfer->tx_buf, cnt);

	remainder = xfer->len % 4;
	if (remainder > 0) {
		reg_val = 0;
		memcpy(&reg_val, xfer->tx_buf + (cnt * 4), remainder);
		writel(reg_val, mdata->base + SPI_TX_DATA_REG);
	}

	mtk_spi_enable_transfer(master);

	return 1;
}