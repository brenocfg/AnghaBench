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
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int mpt_HardResetHandler (int /*<<< orphan*/ *,int) ; 
 int mpt_SoftResetHandler (int /*<<< orphan*/ *,int) ; 

int
mpt_Soft_Hard_ResetHandler(MPT_ADAPTER *ioc, int sleepFlag) {
	int ret = -1;

	ret = mpt_SoftResetHandler(ioc, sleepFlag);
	if (ret == 0)
		return ret;
	ret = mpt_HardResetHandler(ioc, sleepFlag);
	return ret;
}