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
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_cpu_info ; 
 int /*<<< orphan*/  isst_if_online_id ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isst_if_cpu_info_exit(void)
{
	cpuhp_remove_state(isst_if_online_id);
	kfree(isst_cpu_info);
}