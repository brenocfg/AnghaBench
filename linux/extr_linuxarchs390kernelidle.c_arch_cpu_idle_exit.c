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
 int /*<<< orphan*/  CIF_MCCK_PENDING ; 
 int /*<<< orphan*/  local_mcck_enable () ; 
 int /*<<< orphan*/  s390_handle_mcck () ; 
 scalar_t__ test_cpu_flag (int /*<<< orphan*/ ) ; 

void arch_cpu_idle_exit(void)
{
	local_mcck_enable();
	if (test_cpu_flag(CIF_MCCK_PENDING))
		s390_handle_mcck();
}