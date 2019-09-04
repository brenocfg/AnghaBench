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
 int /*<<< orphan*/  hash_value_early_read ; 
 int /*<<< orphan*/  pm_trace_nb ; 
 int /*<<< orphan*/  read_magic_time () ; 
 int /*<<< orphan*/  register_pm_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int early_resume_init(void)
{
	hash_value_early_read = read_magic_time();
	register_pm_notifier(&pm_trace_nb);
	return 0;
}