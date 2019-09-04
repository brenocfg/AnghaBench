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
struct si1133_data {int* adc_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_PARAM_REG_ADCSENS (int /*<<< orphan*/ ) ; 
 int si1133_get_int_time_index (int,int) ; 
 int si1133_param_set (struct si1133_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si1133_set_integration_time(struct si1133_data *data, u8 adc,
				       int milliseconds, int nanoseconds)
{
	int index;

	index = si1133_get_int_time_index(milliseconds, nanoseconds);
	if (index < 0)
		return index;

	data->adc_sens[adc] &= 0xF0;
	data->adc_sens[adc] |= index;

	return si1133_param_set(data, SI1133_PARAM_REG_ADCSENS(0),
				data->adc_sens[adc]);
}