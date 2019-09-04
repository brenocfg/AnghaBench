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
 int /*<<< orphan*/  SI1133_ADCMUX_MASK ; 
 int si1133_update_adcconfig (struct si1133_data*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int si1133_set_adcmux(struct si1133_data *data, u8 adc, u8 mux)
{
	if ((mux & data->adc_config[adc]) == mux)
		return 0; /* mux already set to correct value */

	return si1133_update_adcconfig(data, adc, SI1133_ADCMUX_MASK, 0, mux);
}