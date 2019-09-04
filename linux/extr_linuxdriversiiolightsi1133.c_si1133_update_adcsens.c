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
typedef  int u32 ;
struct si1133_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_PARAM_REG_ADCSENS (int /*<<< orphan*/ ) ; 
 int si1133_chan_set_adcsens (struct si1133_data*,int /*<<< orphan*/ ,int) ; 
 int si1133_param_query (struct si1133_data*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int si1133_update_adcsens(struct si1133_data *data, u8 mask,
				 u8 shift, u8 value)
{
	int err;
	u32 adc_sens;

	err = si1133_param_query(data, SI1133_PARAM_REG_ADCSENS(0),
				 &adc_sens);
	if (err)
		return err;

	adc_sens &= ~mask;
	adc_sens |= (value << shift);

	return si1133_chan_set_adcsens(data, 0, adc_sens);
}