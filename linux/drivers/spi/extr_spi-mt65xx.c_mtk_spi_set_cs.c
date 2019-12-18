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
typedef  int /*<<< orphan*/  u32 ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct mtk_spi {int /*<<< orphan*/  state; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_SPI_IDLE ; 
 int /*<<< orphan*/  SPI_CMD_PAUSE_EN ; 
 scalar_t__ SPI_CMD_REG ; 
 int /*<<< orphan*/  mtk_spi_reset (struct mtk_spi*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct mtk_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_spi_set_cs(struct spi_device *spi, bool enable)
{
	u32 reg_val;
	struct mtk_spi *mdata = spi_master_get_devdata(spi->master);

	reg_val = readl(mdata->base + SPI_CMD_REG);
	if (!enable) {
		reg_val |= SPI_CMD_PAUSE_EN;
		writel(reg_val, mdata->base + SPI_CMD_REG);
	} else {
		reg_val &= ~SPI_CMD_PAUSE_EN;
		writel(reg_val, mdata->base + SPI_CMD_REG);
		mdata->state = MTK_SPI_IDLE;
		mtk_spi_reset(mdata);
	}
}