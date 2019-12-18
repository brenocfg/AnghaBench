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
typedef  scalar_t__ u8 ;
struct stmpe_adc {scalar_t__ channel; int value; int /*<<< orphan*/  lock; int /*<<< orphan*/  stmpe; int /*<<< orphan*/  completion; } ;
struct iio_chan_spec {scalar_t__ channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STMPE_ADC_CH (scalar_t__) ; 
 scalar_t__ STMPE_ADC_LAST_NR ; 
 int /*<<< orphan*/  STMPE_ADC_TIMEOUT ; 
 int /*<<< orphan*/  STMPE_REG_ADC_CAPT ; 
 int /*<<< orphan*/  STMPE_REG_ADC_INT_STA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmpe_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_read_voltage(struct stmpe_adc *info,
		struct iio_chan_spec const *chan, int *val)
{
	long ret;

	mutex_lock(&info->lock);

	reinit_completion(&info->completion);

	info->channel = (u8)chan->channel;

	if (info->channel > STMPE_ADC_LAST_NR) {
		mutex_unlock(&info->lock);
		return -EINVAL;
	}

	stmpe_reg_write(info->stmpe, STMPE_REG_ADC_CAPT,
			STMPE_ADC_CH(info->channel));

	ret = wait_for_completion_timeout(&info->completion, STMPE_ADC_TIMEOUT);

	if (ret <= 0) {
		stmpe_reg_write(info->stmpe, STMPE_REG_ADC_INT_STA,
				STMPE_ADC_CH(info->channel));
		mutex_unlock(&info->lock);
		return -ETIMEDOUT;
	}

	*val = info->value;

	mutex_unlock(&info->lock);

	return 0;
}