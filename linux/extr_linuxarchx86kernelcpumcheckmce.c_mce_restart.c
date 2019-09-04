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
 int /*<<< orphan*/  mce_cpu_restart ; 
 int /*<<< orphan*/  mce_timer_delete_all () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mce_restart(void)
{
	mce_timer_delete_all();
	on_each_cpu(mce_cpu_restart, NULL, 1);
}