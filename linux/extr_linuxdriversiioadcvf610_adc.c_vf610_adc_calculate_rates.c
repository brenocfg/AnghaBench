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
struct vf610_adc_feature {size_t conv_mode; int clk_div; int default_sample_time; int lst_adder_index; } ;
struct vf610_adc {unsigned long* max_adck_rate; unsigned long* sample_freq_avail; int /*<<< orphan*/  clk; struct vf610_adc_feature adc_feature; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 unsigned long NSEC_PER_SEC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int fls (int) ; 
 int* vf610_hw_avgs ; 
 int* vf610_lst_adder ; 

__attribute__((used)) static inline void vf610_adc_calculate_rates(struct vf610_adc *info)
{
	struct vf610_adc_feature *adc_feature = &info->adc_feature;
	unsigned long adck_rate, ipg_rate = clk_get_rate(info->clk);
	u32 adck_period, lst_addr_min;
	int divisor, i;

	adck_rate = info->max_adck_rate[adc_feature->conv_mode];

	if (adck_rate) {
		/* calculate clk divider which is within specification */
		divisor = ipg_rate / adck_rate;
		adc_feature->clk_div = 1 << fls(divisor + 1);
	} else {
		/* fall-back value using a safe divisor */
		adc_feature->clk_div = 8;
	}

	adck_rate = ipg_rate / adc_feature->clk_div;

	/*
	 * Determine the long sample time adder value to be used based
	 * on the default minimum sample time provided.
	 */
	adck_period = NSEC_PER_SEC / adck_rate;
	lst_addr_min = adc_feature->default_sample_time / adck_period;
	for (i = 0; i < ARRAY_SIZE(vf610_lst_adder); i++) {
		if (vf610_lst_adder[i] > lst_addr_min) {
			adc_feature->lst_adder_index = i;
			break;
		}
	}

	/*
	 * Calculate ADC sample frequencies
	 * Sample time unit is ADCK cycles. ADCK clk source is ipg clock,
	 * which is the same as bus clock.
	 *
	 * ADC conversion time = SFCAdder + AverageNum x (BCT + LSTAdder)
	 * SFCAdder: fixed to 6 ADCK cycles
	 * AverageNum: 1, 4, 8, 16, 32 samples for hardware average.
	 * BCT (Base Conversion Time): fixed to 25 ADCK cycles for 12 bit mode
	 * LSTAdder(Long Sample Time): 3, 5, 7, 9, 13, 17, 21, 25 ADCK cycles
	 */
	for (i = 0; i < ARRAY_SIZE(vf610_hw_avgs); i++)
		info->sample_freq_avail[i] =
			adck_rate / (6 + vf610_hw_avgs[i] *
			 (25 + vf610_lst_adder[adc_feature->lst_adder_index]));
}