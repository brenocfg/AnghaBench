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
struct iadc_chip {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IADC_CONV_TIME_MAX_US ; 
 unsigned int IADC_CONV_TIME_MIN_US ; 
 int /*<<< orphan*/  IADC_STATUS1 ; 
 int /*<<< orphan*/  IADC_STATUS1_EOC ; 
 int /*<<< orphan*/  IADC_STATUS1_REQ_STS_EOC_MASK ; 
 int iadc_read (struct iadc_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iadc_status_show (struct iadc_chip*) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iadc_poll_wait_eoc(struct iadc_chip *iadc, unsigned int interval_us)
{
	unsigned int count, retry;
	int ret;
	u8 sta1;

	retry = interval_us / IADC_CONV_TIME_MIN_US;

	for (count = 0; count < retry; count++) {
		ret = iadc_read(iadc, IADC_STATUS1, &sta1);
		if (ret < 0)
			return ret;

		sta1 &= IADC_STATUS1_REQ_STS_EOC_MASK;
		if (sta1 == IADC_STATUS1_EOC)
			return 0;

		usleep_range(IADC_CONV_TIME_MIN_US, IADC_CONV_TIME_MAX_US);
	}

	iadc_status_show(iadc);

	return -ETIMEDOUT;
}