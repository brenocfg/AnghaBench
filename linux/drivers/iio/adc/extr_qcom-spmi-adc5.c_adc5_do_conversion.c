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
typedef  int /*<<< orphan*/  u16 ;
struct iio_chan_spec {int dummy; } ;
struct adc5_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; scalar_t__ poll_eoc; } ;
struct adc5_channel_prop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC5_CONV_TIMEOUT ; 
 int adc5_configure (struct adc5_chip*,struct adc5_channel_prop*) ; 
 int adc5_poll_wait_eoc (struct adc5_chip*) ; 
 int adc5_read_voltage_data (struct adc5_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc5_do_conversion(struct adc5_chip *adc,
			struct adc5_channel_prop *prop,
			struct iio_chan_spec const *chan,
			u16 *data_volt, u16 *data_cur)
{
	int ret;

	mutex_lock(&adc->lock);

	ret = adc5_configure(adc, prop);
	if (ret) {
		pr_err("ADC configure failed with %d\n", ret);
		goto unlock;
	}

	if (adc->poll_eoc) {
		ret = adc5_poll_wait_eoc(adc);
		if (ret < 0) {
			pr_err("EOC bit not set\n");
			goto unlock;
		}
	} else {
		ret = wait_for_completion_timeout(&adc->complete,
							ADC5_CONV_TIMEOUT);
		if (!ret) {
			pr_debug("Did not get completion timeout.\n");
			ret = adc5_poll_wait_eoc(adc);
			if (ret < 0) {
				pr_err("EOC bit not set\n");
				goto unlock;
			}
		}
	}

	ret = adc5_read_voltage_data(adc, data_volt);
unlock:
	mutex_unlock(&adc->lock);

	return ret;
}