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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ div_u64 (scalar_t__,int) ; 
 int /*<<< orphan*/  task_cputime_adjusted (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static u64 current_task_runtime_100ns(void)
{
	u64 utime, stime;

	task_cputime_adjusted(current, &utime, &stime);

	return div_u64(utime + stime, 100);
}