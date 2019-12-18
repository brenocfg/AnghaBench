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
struct lpss_config {scalar_t__ reg_cs_ctrl; scalar_t__ reg_ssp; scalar_t__ reg_general; scalar_t__ offset; } ;
struct driver_data {TYPE_1__* controller_info; scalar_t__ ioaddr; scalar_t__ lpss_base; } ;
struct TYPE_2__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 int LPSS_CS_CONTROL_CS_HIGH ; 
 int LPSS_CS_CONTROL_SW_MODE ; 
 int LPSS_GENERAL_REG_RXTO_HOLDOFF_DISABLE ; 
 int __lpss_ssp_read_priv (struct driver_data*,scalar_t__) ; 
 int /*<<< orphan*/  __lpss_ssp_write_priv (struct driver_data*,scalar_t__,int) ; 
 struct lpss_config* lpss_get_config (struct driver_data*) ; 

__attribute__((used)) static void lpss_ssp_setup(struct driver_data *drv_data)
{
	const struct lpss_config *config;
	u32 value;

	config = lpss_get_config(drv_data);
	drv_data->lpss_base = drv_data->ioaddr + config->offset;

	/* Enable software chip select control */
	value = __lpss_ssp_read_priv(drv_data, config->reg_cs_ctrl);
	value &= ~(LPSS_CS_CONTROL_SW_MODE | LPSS_CS_CONTROL_CS_HIGH);
	value |= LPSS_CS_CONTROL_SW_MODE | LPSS_CS_CONTROL_CS_HIGH;
	__lpss_ssp_write_priv(drv_data, config->reg_cs_ctrl, value);

	/* Enable multiblock DMA transfers */
	if (drv_data->controller_info->enable_dma) {
		__lpss_ssp_write_priv(drv_data, config->reg_ssp, 1);

		if (config->reg_general >= 0) {
			value = __lpss_ssp_read_priv(drv_data,
						     config->reg_general);
			value |= LPSS_GENERAL_REG_RXTO_HOLDOFF_DISABLE;
			__lpss_ssp_write_priv(drv_data,
					      config->reg_general, value);
		}
	}
}