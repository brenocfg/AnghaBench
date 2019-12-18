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
struct iadc_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; scalar_t__ poll_eoc; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int IADC_CONV_TIME_MIN_US ; 
 int /*<<< orphan*/  IADC_DEF_AVG_SAMPLES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int iadc_configure (struct iadc_chip*,int) ; 
 int iadc_poll_wait_eoc (struct iadc_chip*,int) ; 
 int iadc_read_result (struct iadc_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iadc_set_state (struct iadc_chip*,int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (unsigned int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iadc_do_conversion(struct iadc_chip *iadc, int chan, u16 *data)
{
	unsigned int wait;
	int ret;

	ret = iadc_configure(iadc, chan);
	if (ret < 0)
		goto exit;

	wait = BIT(IADC_DEF_AVG_SAMPLES) * IADC_CONV_TIME_MIN_US * 2;

	if (iadc->poll_eoc) {
		ret = iadc_poll_wait_eoc(iadc, wait);
	} else {
		ret = wait_for_completion_timeout(&iadc->complete,
			usecs_to_jiffies(wait));
		if (!ret)
			ret = -ETIMEDOUT;
		else
			/* double check conversion status */
			ret = iadc_poll_wait_eoc(iadc, IADC_CONV_TIME_MIN_US);
	}

	if (!ret)
		ret = iadc_read_result(iadc, data);
exit:
	iadc_set_state(iadc, false);
	if (ret < 0)
		dev_err(iadc->dev, "conversion failed\n");

	return ret;
}