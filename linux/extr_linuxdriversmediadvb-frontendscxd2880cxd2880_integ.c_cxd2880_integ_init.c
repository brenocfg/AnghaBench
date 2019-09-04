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
struct cxd2880_tnrdmd {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_WAIT_INIT_INTVL ; 
 scalar_t__ CXD2880_TNRDMD_WAIT_INIT_TIMEOUT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int cxd2880_tnrdmd_check_internal_cpu_status (struct cxd2880_tnrdmd*,scalar_t__*) ; 
 int cxd2880_tnrdmd_init1 (struct cxd2880_tnrdmd*) ; 
 int cxd2880_tnrdmd_init2 (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

int cxd2880_integ_init(struct cxd2880_tnrdmd *tnr_dmd)
{
	int ret;
	ktime_t start;
	u8 cpu_task_completed = 0;

	if (!tnr_dmd)
		return -EINVAL;

	ret = cxd2880_tnrdmd_init1(tnr_dmd);
	if (ret)
		return ret;

	start = ktime_get();

	while (1) {
		ret =
		    cxd2880_tnrdmd_check_internal_cpu_status(tnr_dmd,
						     &cpu_task_completed);
		if (ret)
			return ret;

		if (cpu_task_completed)
			break;

		if (ktime_to_ms(ktime_sub(ktime_get(), start)) >
					CXD2880_TNRDMD_WAIT_INIT_TIMEOUT)
			return -ETIMEDOUT;

		usleep_range(CXD2880_TNRDMD_WAIT_INIT_INTVL,
			     CXD2880_TNRDMD_WAIT_INIT_INTVL + 1000);
	}

	return cxd2880_tnrdmd_init2(tnr_dmd);
}