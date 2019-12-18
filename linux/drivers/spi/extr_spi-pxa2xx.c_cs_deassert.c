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
struct chip_data {int /*<<< orphan*/  gpio_cs_inverted; scalar_t__ gpiod_cs; int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CE4100_SSP ; 
 int /*<<< orphan*/  PXA2XX_CS_DEASSERT ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_BSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 scalar_t__ is_lpss_ssp (struct driver_data*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lpss_ssp_cs_control (struct spi_device*,int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int pxa2xx_spi_read (struct driver_data*,int /*<<< orphan*/ ) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void cs_deassert(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata(spi);
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	unsigned long timeout;

	if (drv_data->ssp_type == CE4100_SSP)
		return;

	/* Wait until SSP becomes idle before deasserting the CS */
	timeout = jiffies + msecs_to_jiffies(10);
	while (pxa2xx_spi_read(drv_data, SSSR) & SSSR_BSY &&
	       !time_after(jiffies, timeout))
		cpu_relax();

	if (chip->cs_control) {
		chip->cs_control(PXA2XX_CS_DEASSERT);
		return;
	}

	if (chip->gpiod_cs) {
		gpiod_set_value(chip->gpiod_cs, !chip->gpio_cs_inverted);
		return;
	}

	if (is_lpss_ssp(drv_data))
		lpss_ssp_cs_control(spi, false);
}