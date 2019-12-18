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
struct spi_device {int /*<<< orphan*/  controller; } ;
struct driver_data {scalar_t__ ssp_type; } ;
struct chip_data {int /*<<< orphan*/  gpio_cs_inverted; scalar_t__ gpiod_cs; int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  frm; } ;

/* Variables and functions */
 scalar_t__ CE4100_SSP ; 
 int /*<<< orphan*/  PXA2XX_CS_ASSERT ; 
 int /*<<< orphan*/  SSSR ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ is_lpss_ssp (struct driver_data*) ; 
 int /*<<< orphan*/  lpss_ssp_cs_control (struct spi_device*,int) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_assert(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata(spi);
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);

	if (drv_data->ssp_type == CE4100_SSP) {
		pxa2xx_spi_write(drv_data, SSSR, chip->frm);
		return;
	}

	if (chip->cs_control) {
		chip->cs_control(PXA2XX_CS_ASSERT);
		return;
	}

	if (chip->gpiod_cs) {
		gpiod_set_value(chip->gpiod_cs, chip->gpio_cs_inverted);
		return;
	}

	if (is_lpss_ssp(drv_data))
		lpss_ssp_cs_control(spi, true);
}