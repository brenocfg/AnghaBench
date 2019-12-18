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
typedef  int u32 ;
struct sc27xx_adc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  big_scale_graph ; 
 int sc27xx_adc_to_volt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sc27xx_adc_volt_ratio (struct sc27xx_adc_data*,int,int,int*,int*) ; 
 int /*<<< orphan*/  small_scale_graph ; 

__attribute__((used)) static int sc27xx_adc_convert_volt(struct sc27xx_adc_data *data, int channel,
				   int scale, int raw_adc)
{
	u32 numerator, denominator;
	u32 volt;

	/*
	 * Convert ADC values to voltage values according to the linear graph,
	 * and channel 5 and channel 1 has been calibrated, so we can just
	 * return the voltage values calculated by the linear graph. But other
	 * channels need be calculated to the real voltage values with the
	 * voltage ratio.
	 */
	switch (channel) {
	case 5:
		return sc27xx_adc_to_volt(&big_scale_graph, raw_adc);

	case 1:
		return sc27xx_adc_to_volt(&small_scale_graph, raw_adc);

	default:
		volt = sc27xx_adc_to_volt(&small_scale_graph, raw_adc);
		break;
	}

	sc27xx_adc_volt_ratio(data, channel, scale, &numerator, &denominator);

	return (volt * denominator + numerator / 2) / numerator;
}