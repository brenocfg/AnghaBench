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
struct sirf_data {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long SIRF_ACTIVATE_TIMEOUT ; 
 unsigned long SIRF_HIBERNATE_TIMEOUT ; 
 int /*<<< orphan*/  sirf_pulse_on_off (struct sirf_data*) ; 
 int sirf_wait_for_power_state (struct sirf_data*,int,unsigned long) ; 

__attribute__((used)) static int sirf_set_active(struct sirf_data *data, bool active)
{
	unsigned long timeout;
	int retries = 3;
	int ret;

	if (active)
		timeout = SIRF_ACTIVATE_TIMEOUT;
	else
		timeout = SIRF_HIBERNATE_TIMEOUT;

	do {
		sirf_pulse_on_off(data);
		ret = sirf_wait_for_power_state(data, active, timeout);
		if (ret < 0) {
			if (ret == -ETIMEDOUT)
				continue;

			return ret;
		}

		break;
	} while (retries--);

	if (retries < 0)
		return -ETIMEDOUT;

	return 0;
}