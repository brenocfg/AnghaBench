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
 int /*<<< orphan*/  VCLOCK_PVCLOCK ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct pvclock_vsyscall_time_info* pvti_cpu0_va ; 
 int /*<<< orphan*/  vclock_was_used (int /*<<< orphan*/ ) ; 

void pvclock_set_pvti_cpu0_va(struct pvclock_vsyscall_time_info *pvti)
{
	WARN_ON(vclock_was_used(VCLOCK_PVCLOCK));
	pvti_cpu0_va = pvti;
}