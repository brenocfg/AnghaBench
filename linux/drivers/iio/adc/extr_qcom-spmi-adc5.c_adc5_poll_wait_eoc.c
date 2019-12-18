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
struct adc5_chip {int dummy; } ;
typedef  int /*<<< orphan*/  status1 ;

/* Variables and functions */
 int /*<<< orphan*/  ADC5_CONV_TIME_MAX_US ; 
 int /*<<< orphan*/  ADC5_CONV_TIME_MIN_US ; 
 unsigned int ADC5_CONV_TIME_RETRY ; 
 int /*<<< orphan*/  ADC5_USR_STATUS1 ; 
 int /*<<< orphan*/  ADC5_USR_STATUS1_EOC ; 
 int /*<<< orphan*/  ADC5_USR_STATUS1_REQ_STS_EOC_MASK ; 
 int ETIMEDOUT ; 
 int adc5_read (struct adc5_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc5_poll_wait_eoc(struct adc5_chip *adc)
{
	unsigned int count, retry = ADC5_CONV_TIME_RETRY;
	u8 status1;
	int ret;

	for (count = 0; count < retry; count++) {
		ret = adc5_read(adc, ADC5_USR_STATUS1, &status1,
							sizeof(status1));
		if (ret)
			return ret;

		status1 &= ADC5_USR_STATUS1_REQ_STS_EOC_MASK;
		if (status1 == ADC5_USR_STATUS1_EOC)
			return 0;

		usleep_range(ADC5_CONV_TIME_MIN_US, ADC5_CONV_TIME_MAX_US);
	}

	return -ETIMEDOUT;
}