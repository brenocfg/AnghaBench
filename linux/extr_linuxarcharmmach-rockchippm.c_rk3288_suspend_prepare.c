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
 int /*<<< orphan*/  PM_SUSPEND_MEM ; 
 int regulator_suspend_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3288_suspend_prepare(void)
{
	return regulator_suspend_prepare(PM_SUSPEND_MEM);
}