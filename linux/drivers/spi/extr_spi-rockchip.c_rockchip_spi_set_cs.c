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
struct spi_master {int dummy; } ;
struct spi_device {size_t chip_select; struct spi_master* master; } ;
struct rockchip_spi {int* cs_asserted; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int /*<<< orphan*/  ROCKCHIP_SPI_CLR_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ROCKCHIP_SPI_SER ; 
 int /*<<< orphan*/  ROCKCHIP_SPI_SET_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void rockchip_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct spi_master *master = spi->master;
	struct rockchip_spi *rs = spi_master_get_devdata(master);
	bool cs_asserted = !enable;

	/* Return immediately for no-op */
	if (cs_asserted == rs->cs_asserted[spi->chip_select])
		return;

	if (cs_asserted) {
		/* Keep things powered as long as CS is asserted */
		pm_runtime_get_sync(rs->dev);

		ROCKCHIP_SPI_SET_BITS(rs->regs + ROCKCHIP_SPI_SER,
				      BIT(spi->chip_select));
	} else {
		ROCKCHIP_SPI_CLR_BITS(rs->regs + ROCKCHIP_SPI_SER,
				      BIT(spi->chip_select));

		/* Drop reference from when we first asserted CS */
		pm_runtime_put(rs->dev);
	}

	rs->cs_asserted[spi->chip_select] = cs_asserted;
}