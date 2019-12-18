#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hw_gpio_pin {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  en; } ;
struct hw_gpio {TYPE_4__ base; } ;
struct hw_ddc {TYPE_3__* regs; struct hw_gpio base; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  clock_en_bit_present; int /*<<< orphan*/  data_en_bit_present; } ;
struct TYPE_7__ {TYPE_1__ ddc; } ;
struct gpio_config_data {TYPE_2__ config; int /*<<< orphan*/  type; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
struct TYPE_10__ {int /*<<< orphan*/  MASK_reg; } ;
struct TYPE_8__ {int /*<<< orphan*/  dc_gpio_aux_ctrl_5; int /*<<< orphan*/  phy_aux_cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  AUX_PAD1_MODE ; 
 int /*<<< orphan*/  AUX_PAD_RXSEL ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DC_GPIO_DDC1CLK_PD_EN ; 
 int /*<<< orphan*/  DC_GPIO_DDC1DATA_PD_EN ; 
 int /*<<< orphan*/  DC_GPIO_SCL_PD_DIS ; 
 int /*<<< orphan*/  DC_GPIO_SDA_PD_DIS ; 
 int /*<<< orphan*/  DC_I2C_DDC1_EDID_DETECT_ENABLE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_EDID_DETECT_MODE ; 
 int /*<<< orphan*/  DC_I2C_DDC1_ENABLE ; 
 int /*<<< orphan*/  DDC_PAD_I2CMODE ; 
 int /*<<< orphan*/  GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE ; 
#define  GPIO_DDC_CONFIG_TYPE_DISABLE_POLLING 132 
#define  GPIO_DDC_CONFIG_TYPE_MODE_AUX 131 
#define  GPIO_DDC_CONFIG_TYPE_MODE_I2C 130 
#define  GPIO_DDC_CONFIG_TYPE_POLL_FOR_CONNECT 129 
#define  GPIO_DDC_CONFIG_TYPE_POLL_FOR_DISCONNECT 128 
 int /*<<< orphan*/  GPIO_DDC_LINE_DDC1 ; 
 int /*<<< orphan*/  GPIO_DDC_LINE_DDC_VGA ; 
 int /*<<< orphan*/  GPIO_DDC_LINE_VIP_PAD ; 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_NULL_HANDLE ; 
 int GPIO_RESULT_OK ; 
 struct hw_ddc* HW_DDC_FROM_BASE (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_GET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dc_gpio_aux_ctrl_5 ; 
 int /*<<< orphan*/  ddc_setup ; 
 TYPE_5__ gpio ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  phy_aux_cntl ; 

__attribute__((used)) static enum gpio_result set_config(
	struct hw_gpio_pin *ptr,
	const struct gpio_config_data *config_data)
{
	struct hw_ddc *ddc = HW_DDC_FROM_BASE(ptr);
	struct hw_gpio *hw_gpio = NULL;
	uint32_t regval;
	uint32_t ddc_data_pd_en = 0;
	uint32_t ddc_clk_pd_en = 0;
	uint32_t aux_pad_mode = 0;

	hw_gpio = &ddc->base;

	if (hw_gpio == NULL) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_NULL_HANDLE;
	}

	regval = REG_GET_3(gpio.MASK_reg,
			DC_GPIO_DDC1DATA_PD_EN, &ddc_data_pd_en,
			DC_GPIO_DDC1CLK_PD_EN, &ddc_clk_pd_en,
			AUX_PAD1_MODE, &aux_pad_mode);

	switch (config_data->config.ddc.type) {
	case GPIO_DDC_CONFIG_TYPE_MODE_I2C:
		/* On plug-in, there is a transient level on the pad
		 * which must be discharged through the internal pull-down.
		 * Enable internal pull-down, 2.5msec discharge time
		 * is required for detection of AUX mode */
		if (hw_gpio->base.en != GPIO_DDC_LINE_VIP_PAD) {
			if (!ddc_data_pd_en || !ddc_clk_pd_en) {

				REG_SET_2(gpio.MASK_reg, regval,
						DC_GPIO_DDC1DATA_PD_EN, 1,
						DC_GPIO_DDC1CLK_PD_EN, 1);

				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			}
		} else {
			uint32_t reg2;
			uint32_t sda_pd_dis = 0;
			uint32_t scl_pd_dis = 0;

			reg2 = REG_GET_2(gpio.MASK_reg,
					DC_GPIO_SDA_PD_DIS, &sda_pd_dis,
					DC_GPIO_SCL_PD_DIS, &scl_pd_dis);

			if (sda_pd_dis) {
				REG_SET(gpio.MASK_reg, regval,
						DC_GPIO_SDA_PD_DIS, 0);

				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			}

			if (!scl_pd_dis) {
				REG_SET(gpio.MASK_reg, regval,
						DC_GPIO_SCL_PD_DIS, 1);

				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			}
		}

		if (aux_pad_mode) {
			/* let pins to get de-asserted
			 * before setting pad to I2C mode */
			if (config_data->config.ddc.data_en_bit_present ||
				config_data->config.ddc.clock_en_bit_present)
				/* [anaumov] in DAL2, there was
				 * dc_service_delay_in_microseconds(2000); */
				msleep(2);

			/* set the I2C pad mode */
			/* read the register again,
			 * some bits may have been changed */
			REG_UPDATE(gpio.MASK_reg,
					AUX_PAD1_MODE, 0);
		}

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
		if (ddc->regs->dc_gpio_aux_ctrl_5 != 0) {
				REG_UPDATE(dc_gpio_aux_ctrl_5, DDC_PAD_I2CMODE, 1);
		}
		//set  DC_IO_aux_rxsel = 2'b01
		if (ddc->regs->phy_aux_cntl != 0) {
				REG_UPDATE(phy_aux_cntl, AUX_PAD_RXSEL, 1);
		}
#endif
		return GPIO_RESULT_OK;
	case GPIO_DDC_CONFIG_TYPE_MODE_AUX:
		/* set the AUX pad mode */
		if (!aux_pad_mode) {
			REG_SET(gpio.MASK_reg, regval,
					AUX_PAD1_MODE, 1);
		}
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
		if (ddc->regs->dc_gpio_aux_ctrl_5 != 0) {
			REG_UPDATE(dc_gpio_aux_ctrl_5,
					DDC_PAD_I2CMODE, 0);
		}
#endif

		return GPIO_RESULT_OK;
	case GPIO_DDC_CONFIG_TYPE_POLL_FOR_CONNECT:
		if ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) {
			REG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 0);
			return GPIO_RESULT_OK;
		}
	break;
	case GPIO_DDC_CONFIG_TYPE_POLL_FOR_DISCONNECT:
		if ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) {
			REG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 1);
			return GPIO_RESULT_OK;
		}
	break;
	case GPIO_DDC_CONFIG_TYPE_DISABLE_POLLING:
		if ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) {
			REG_UPDATE_2(ddc_setup,
				DC_I2C_DDC1_ENABLE, 0,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 0);
			return GPIO_RESULT_OK;
		}
	break;
	}

	BREAK_TO_DEBUGGER();

	return GPIO_RESULT_NON_SPECIFIC_ERROR;
}