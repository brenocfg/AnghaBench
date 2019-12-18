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
struct watchdog_device {unsigned int timeout; } ;
struct arm_smccc_res {scalar_t__ a0; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  IMX_SIP_TIMER ; 
 int /*<<< orphan*/  IMX_SIP_TIMER_SET_TIMEOUT_WDOG ; 
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int imx_sc_wdt_set_timeout(struct watchdog_device *wdog,
				unsigned int timeout)
{
	struct arm_smccc_res res;

	wdog->timeout = timeout;
	arm_smccc_smc(IMX_SIP_TIMER, IMX_SIP_TIMER_SET_TIMEOUT_WDOG,
		      timeout * 1000, 0, 0, 0, 0, 0, &res);

	return res.a0 ? -EACCES : 0;
}