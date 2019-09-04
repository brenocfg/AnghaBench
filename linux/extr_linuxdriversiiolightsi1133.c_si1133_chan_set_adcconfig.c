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
typedef  size_t u8 ;
struct si1133_data {size_t* adc_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_PARAM_REG_ADCCONFIG (size_t) ; 
 int si1133_param_set (struct si1133_data*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int si1133_chan_set_adcconfig(struct si1133_data *data, u8 adc,
				     u8 adc_config)
{
	int err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCCONFIG(adc),
			       adc_config);
	if (err)
		return err;

	data->adc_config[adc] = adc_config;

	return 0;
}