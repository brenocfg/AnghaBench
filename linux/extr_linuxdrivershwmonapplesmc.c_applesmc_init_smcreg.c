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

/* Variables and functions */
 int INIT_TIMEOUT_MSECS ; 
 scalar_t__ INIT_WAIT_MSECS ; 
 int /*<<< orphan*/  applesmc_destroy_smcreg () ; 
 int applesmc_init_smcreg_try () ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static int applesmc_init_smcreg(void)
{
	int ms, ret;

	for (ms = 0; ms < INIT_TIMEOUT_MSECS; ms += INIT_WAIT_MSECS) {
		ret = applesmc_init_smcreg_try();
		if (!ret) {
			if (ms)
				pr_info("init_smcreg() took %d ms\n", ms);
			return 0;
		}
		msleep(INIT_WAIT_MSECS);
	}

	applesmc_destroy_smcreg();

	return ret;
}