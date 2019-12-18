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
struct spi_device {int chip_select; int /*<<< orphan*/  controller; } ;
struct lpss_config {int cs_sel_mask; int cs_sel_shift; int /*<<< orphan*/  reg_cs_ctrl; } ;
struct driver_data {TYPE_1__* controller; } ;
struct TYPE_2__ {int max_speed_hz; } ;

/* Variables and functions */
 int __lpss_ssp_read_priv (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lpss_ssp_write_priv (struct driver_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpss_ssp_select_cs(struct spi_device *spi,
			       const struct lpss_config *config)
{
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	u32 value, cs;

	if (!config->cs_sel_mask)
		return;

	value = __lpss_ssp_read_priv(drv_data, config->reg_cs_ctrl);

	cs = spi->chip_select;
	cs <<= config->cs_sel_shift;
	if (cs != (value & config->cs_sel_mask)) {
		/*
		 * When switching another chip select output active the
		 * output must be selected first and wait 2 ssp_clk cycles
		 * before changing state to active. Otherwise a short
		 * glitch will occur on the previous chip select since
		 * output select is latched but state control is not.
		 */
		value &= ~config->cs_sel_mask;
		value |= cs;
		__lpss_ssp_write_priv(drv_data,
				      config->reg_cs_ctrl, value);
		ndelay(1000000000 /
		       (drv_data->controller->max_speed_hz / 2));
	}
}