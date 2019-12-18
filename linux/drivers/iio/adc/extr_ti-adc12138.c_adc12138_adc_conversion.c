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
struct iio_chan_spec {int dummy; } ;
struct adc12138 {int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int adc12138_read_conv_data (struct adc12138*,int /*<<< orphan*/ *) ; 
 int adc12138_start_conv (struct adc12138*,struct iio_chan_spec const*) ; 
 int adc12138_wait_eoc (struct adc12138*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adc12138_adc_conversion(struct adc12138 *adc,
				   struct iio_chan_spec const *channel,
				   __be16 *value)
{
	int ret;

	reinit_completion(&adc->complete);

	ret = adc12138_start_conv(adc, channel);
	if (ret)
		return ret;

	ret = adc12138_wait_eoc(adc, msecs_to_jiffies(100));
	if (ret)
		return ret;

	return adc12138_read_conv_data(adc, value);
}