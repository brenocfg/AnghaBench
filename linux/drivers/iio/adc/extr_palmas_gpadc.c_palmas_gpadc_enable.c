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
struct palmas_gpadc {unsigned int extended_delay; unsigned int ch0_current; unsigned int ch3_current; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_GPADC_BASE ; 
 int /*<<< orphan*/  PALMAS_GPADC_CTRL1 ; 
 unsigned int PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_MASK ; 
 unsigned int PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_SHIFT ; 
 unsigned int PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_MASK ; 
 unsigned int PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_SHIFT ; 
 unsigned int PALMAS_GPADC_CTRL1_GPADC_FORCE ; 
 int /*<<< orphan*/  PALMAS_GPADC_RT_CTRL ; 
 unsigned int PALMAS_GPADC_RT_CTRL_EXTEND_DELAY ; 
 unsigned int PALMAS_GPADC_RT_CTRL_EXTEND_DELAY_SHIFT ; 
 int /*<<< orphan*/  PALMAS_GPADC_SW_SELECT ; 
 int PALMAS_GPADC_SW_SELECT_SW_CONV0_SEL_MASK ; 
 int PALMAS_GPADC_SW_SELECT_SW_CONV_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int palmas_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int palmas_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_gpadc_enable(struct palmas_gpadc *adc, int adc_chan,
			       int enable)
{
	unsigned int mask, val;
	int ret;

	if (enable) {
		val = (adc->extended_delay
			<< PALMAS_GPADC_RT_CTRL_EXTEND_DELAY_SHIFT);
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
					PALMAS_GPADC_RT_CTRL,
					PALMAS_GPADC_RT_CTRL_EXTEND_DELAY, val);
		if (ret < 0) {
			dev_err(adc->dev, "RT_CTRL update failed: %d\n", ret);
			return ret;
		}

		mask = (PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_MASK |
			PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_MASK |
			PALMAS_GPADC_CTRL1_GPADC_FORCE);
		val = (adc->ch0_current
			<< PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_SHIFT);
		val |= (adc->ch3_current
			<< PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_SHIFT);
		val |= PALMAS_GPADC_CTRL1_GPADC_FORCE;
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_CTRL1, mask, val);
		if (ret < 0) {
			dev_err(adc->dev,
				"Failed to update current setting: %d\n", ret);
			return ret;
		}

		mask = (PALMAS_GPADC_SW_SELECT_SW_CONV0_SEL_MASK |
			PALMAS_GPADC_SW_SELECT_SW_CONV_EN);
		val = (adc_chan | PALMAS_GPADC_SW_SELECT_SW_CONV_EN);
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT, mask, val);
		if (ret < 0) {
			dev_err(adc->dev, "SW_SELECT update failed: %d\n", ret);
			return ret;
		}
	} else {
		ret = palmas_write(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT, 0);
		if (ret < 0)
			dev_err(adc->dev, "SW_SELECT write failed: %d\n", ret);

		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_CTRL1,
				PALMAS_GPADC_CTRL1_GPADC_FORCE, 0);
		if (ret < 0) {
			dev_err(adc->dev, "CTRL1 update failed: %d\n", ret);
			return ret;
		}
	}

	return ret;
}