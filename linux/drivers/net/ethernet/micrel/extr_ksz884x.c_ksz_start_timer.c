#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ expires; } ;
struct ksz_timer_info {int max; TYPE_1__ timer; scalar_t__ cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void ksz_start_timer(struct ksz_timer_info *info, int time)
{
	info->cnt = 0;
	info->timer.expires = jiffies + time;
	add_timer(&info->timer);

	/* infinity */
	info->max = -1;
}