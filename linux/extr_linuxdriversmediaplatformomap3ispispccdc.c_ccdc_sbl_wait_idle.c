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
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ccdc_sbl_busy (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ccdc_sbl_wait_idle(struct isp_ccdc_device *ccdc,
			      unsigned int max_wait)
{
	unsigned int wait = 0;

	if (max_wait == 0)
		max_wait = 10000; /* 10 ms */

	for (wait = 0; wait <= max_wait; wait++) {
		if (!ccdc_sbl_busy(ccdc))
			return 0;

		rmb();
		udelay(1);
	}

	return -EBUSY;
}