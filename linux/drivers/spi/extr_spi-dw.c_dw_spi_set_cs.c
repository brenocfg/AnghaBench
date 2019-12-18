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
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  controller; } ;
struct dw_spi {scalar_t__ cs_override; } ;
struct chip_data {int /*<<< orphan*/  (* cs_control ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_SPI_SER ; 
 int /*<<< orphan*/  dw_writel (struct dw_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw_spi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

void dw_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct dw_spi *dws = spi_controller_get_devdata(spi->controller);
	struct chip_data *chip = spi_get_ctldata(spi);

	if (chip && chip->cs_control)
		chip->cs_control(enable);

	if (enable)
		dw_writel(dws, DW_SPI_SER, BIT(spi->chip_select));
	else if (dws->cs_override)
		dw_writel(dws, DW_SPI_SER, 0);
}