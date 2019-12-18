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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_scan_work ; 
 scalar_t__ ap_suspend_flag ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static void ap_config_timeout(struct timer_list *unused)
{
	if (ap_suspend_flag)
		return;
	queue_work(system_long_wq, &ap_scan_work);
}