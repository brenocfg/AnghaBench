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
typedef  int /*<<< orphan*/  u8 ;
struct adc5_chip {int /*<<< orphan*/  complete; int /*<<< orphan*/  poll_eoc; } ;
struct adc5_channel_prop {int /*<<< orphan*/  hw_settle_time; int /*<<< orphan*/  channel; int /*<<< orphan*/  avg_samples; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ADC5_USR_CONV_REQ_REQ ; 
 int /*<<< orphan*/  ADC5_USR_DIG_PARAM ; 
 int /*<<< orphan*/  ADC5_USR_EN_CTL1_ADC_EN ; 
 scalar_t__ ADC5_USR_FAST_AVG_CTL_SAMPLES_MASK ; 
 scalar_t__ ADC5_USR_HW_SETTLE_DELAY_MASK ; 
 int adc5_read (struct adc5_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  adc5_update_dig_param (struct adc5_chip*,struct adc5_channel_prop*,int /*<<< orphan*/ *) ; 
 int adc5_write (struct adc5_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adc5_configure(struct adc5_chip *adc,
			struct adc5_channel_prop *prop)
{
	int ret;
	u8 buf[6];

	/* Read registers 0x42 through 0x46 */
	ret = adc5_read(adc, ADC5_USR_DIG_PARAM, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	/* Digital param selection */
	adc5_update_dig_param(adc, prop, &buf[0]);

	/* Update fast average sample value */
	buf[1] &= (u8) ~ADC5_USR_FAST_AVG_CTL_SAMPLES_MASK;
	buf[1] |= prop->avg_samples;

	/* Select ADC channel */
	buf[2] = prop->channel;

	/* Select HW settle delay for channel */
	buf[3] &= (u8) ~ADC5_USR_HW_SETTLE_DELAY_MASK;
	buf[3] |= prop->hw_settle_time;

	/* Select ADC enable */
	buf[4] |= ADC5_USR_EN_CTL1_ADC_EN;

	/* Select CONV request */
	buf[5] |= ADC5_USR_CONV_REQ_REQ;

	if (!adc->poll_eoc)
		reinit_completion(&adc->complete);

	return adc5_write(adc, ADC5_USR_DIG_PARAM, buf, sizeof(buf));
}