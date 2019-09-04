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
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct bme680_spi_bus_context {int current_page; struct spi_device* spi; } ;

/* Variables and functions */
 int BME680_REG_STATUS ; 
 int BME680_SPI_MEM_PAGE_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_write (struct spi_device*,int*,int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 

__attribute__((used)) static int bme680_regmap_spi_select_page(
	struct bme680_spi_bus_context *ctx, u8 reg)
{
	struct spi_device *spi = ctx->spi;
	int ret;
	u8 buf[2];
	u8 page = (reg & 0x80) ? 0 : 1; /* Page "1" is low range */

	if (page == ctx->current_page)
		return 0;

	/*
	 * Data sheet claims we're only allowed to change bit 4, so we must do
	 * a read-modify-write on each and every page select
	 */
	buf[0] = BME680_REG_STATUS;
	ret = spi_write_then_read(spi, buf, 1, buf + 1, 1);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to set page %u\n", page);
		return ret;
	}

	buf[0] = BME680_REG_STATUS;
	if (page)
		buf[1] |= BME680_SPI_MEM_PAGE_BIT;
	else
		buf[1] &= ~BME680_SPI_MEM_PAGE_BIT;

	ret = spi_write(spi, buf, 2);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to set page %u\n", page);
		return ret;
	}

	ctx->current_page = page;

	return 0;
}