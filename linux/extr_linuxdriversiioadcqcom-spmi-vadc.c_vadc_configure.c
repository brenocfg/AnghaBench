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
struct vadc_priv {int dummy; } ;
struct vadc_channel_prop {int channel; int decimation; int hw_settle_time; int avg_samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  VADC_ADC_CH_SEL_CTL ; 
 int VADC_ADC_DIG_DEC_RATIO_SEL_SHIFT ; 
 int /*<<< orphan*/  VADC_ADC_DIG_PARAM ; 
 int VADC_ADC_TRIM_EN ; 
 int VADC_AMUX_TRIM_EN ; 
 int /*<<< orphan*/  VADC_FAST_AVG_CTL ; 
 int /*<<< orphan*/  VADC_FAST_AVG_EN ; 
 int VADC_FAST_AVG_EN_SET ; 
 int /*<<< orphan*/  VADC_HW_SETTLE_DELAY ; 
 int /*<<< orphan*/  VADC_MODE_CTL ; 
 int VADC_OP_MODE_NORMAL ; 
 int VADC_OP_MODE_SHIFT ; 
 int vadc_write (struct vadc_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vadc_configure(struct vadc_priv *vadc,
			  struct vadc_channel_prop *prop)
{
	u8 decimation, mode_ctrl;
	int ret;

	/* Mode selection */
	mode_ctrl = (VADC_OP_MODE_NORMAL << VADC_OP_MODE_SHIFT) |
		     VADC_ADC_TRIM_EN | VADC_AMUX_TRIM_EN;
	ret = vadc_write(vadc, VADC_MODE_CTL, mode_ctrl);
	if (ret)
		return ret;

	/* Channel selection */
	ret = vadc_write(vadc, VADC_ADC_CH_SEL_CTL, prop->channel);
	if (ret)
		return ret;

	/* Digital parameter setup */
	decimation = prop->decimation << VADC_ADC_DIG_DEC_RATIO_SEL_SHIFT;
	ret = vadc_write(vadc, VADC_ADC_DIG_PARAM, decimation);
	if (ret)
		return ret;

	/* HW settle time delay */
	ret = vadc_write(vadc, VADC_HW_SETTLE_DELAY, prop->hw_settle_time);
	if (ret)
		return ret;

	ret = vadc_write(vadc, VADC_FAST_AVG_CTL, prop->avg_samples);
	if (ret)
		return ret;

	if (prop->avg_samples)
		ret = vadc_write(vadc, VADC_FAST_AVG_EN, VADC_FAST_AVG_EN_SET);
	else
		ret = vadc_write(vadc, VADC_FAST_AVG_EN, 0);

	return ret;
}