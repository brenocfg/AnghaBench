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
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int WAIT_FOR_FW_RDY ; 
 int WAIT_FOR_INPUT_RDY ; 
 int ish_is_input_ready (struct ishtp_device*) ; 
 int ishtp_fw_is_ready (struct ishtp_device*) ; 
 unsigned long msleep_interruptible (unsigned int) ; 

__attribute__((used)) static int timed_wait_for_timeout(struct ishtp_device *dev, int condition,
				unsigned int timeinc, unsigned int timeout)
{
	bool complete = false;
	int ret;

	do {
		if (condition == WAIT_FOR_FW_RDY) {
			complete = ishtp_fw_is_ready(dev);
		} else if (condition == WAIT_FOR_INPUT_RDY) {
			complete = ish_is_input_ready(dev);
		} else {
			ret = -EINVAL;
			goto out;
		}

		if (!complete) {
			unsigned long left_time;

			left_time = msleep_interruptible(timeinc);
			timeout -= (timeinc - left_time);
		}
	} while (!complete && timeout > 0);

	if (complete)
		ret = 0;
	else
		ret = -EBUSY;

out:
	return ret;
}