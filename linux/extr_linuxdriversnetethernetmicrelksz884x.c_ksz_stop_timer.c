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
struct ksz_timer_info {int /*<<< orphan*/  timer; scalar_t__ max; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz_stop_timer(struct ksz_timer_info *info)
{
	if (info->max) {
		info->max = 0;
		del_timer_sync(&info->timer);
	}
}