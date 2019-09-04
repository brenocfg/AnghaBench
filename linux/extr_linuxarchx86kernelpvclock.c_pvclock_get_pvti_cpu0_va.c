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
struct pvclock_vsyscall_time_info {int dummy; } ;

/* Variables and functions */
 struct pvclock_vsyscall_time_info* pvti_cpu0_va ; 

struct pvclock_vsyscall_time_info *pvclock_get_pvti_cpu0_va(void)
{
	return pvti_cpu0_va;
}