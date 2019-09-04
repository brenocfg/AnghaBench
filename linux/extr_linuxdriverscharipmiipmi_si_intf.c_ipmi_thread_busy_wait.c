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
struct timespec64 {int dummy; } ;
struct smi_info {size_t si_num; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;

/* Variables and functions */
 unsigned int NSEC_PER_USEC ; 
 int SI_SM_CALL_WITH_DELAY ; 
 int /*<<< orphan*/  getnstimeofday64 (struct timespec64*) ; 
 int /*<<< orphan*/  ipmi_si_is_busy (struct timespec64*) ; 
 int /*<<< orphan*/  ipmi_si_set_not_busy (struct timespec64*) ; 
 unsigned int* kipmid_max_busy_us ; 
 size_t num_max_busy_us ; 
 int /*<<< orphan*/  timespec64_add_ns (struct timespec64*,unsigned int) ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ipmi_thread_busy_wait(enum si_sm_result smi_result,
					const struct smi_info *smi_info,
					struct timespec64 *busy_until)
{
	unsigned int max_busy_us = 0;

	if (smi_info->si_num < num_max_busy_us)
		max_busy_us = kipmid_max_busy_us[smi_info->si_num];
	if (max_busy_us == 0 || smi_result != SI_SM_CALL_WITH_DELAY)
		ipmi_si_set_not_busy(busy_until);
	else if (!ipmi_si_is_busy(busy_until)) {
		getnstimeofday64(busy_until);
		timespec64_add_ns(busy_until, max_busy_us*NSEC_PER_USEC);
	} else {
		struct timespec64 now;

		getnstimeofday64(&now);
		if (unlikely(timespec64_compare(&now, busy_until) > 0)) {
			ipmi_si_set_not_busy(busy_until);
			return 0;
		}
	}
	return 1;
}