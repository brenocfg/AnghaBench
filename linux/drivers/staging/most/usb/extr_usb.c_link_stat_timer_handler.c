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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct most_dev {TYPE_1__ link_stat_timer; int /*<<< orphan*/  poll_work_obj; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct most_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  link_stat_timer ; 
 struct most_dev* mdev ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_stat_timer_handler(struct timer_list *t)
{
	struct most_dev *mdev = from_timer(mdev, t, link_stat_timer);

	schedule_work(&mdev->poll_work_obj);
	mdev->link_stat_timer.expires = jiffies + (2 * HZ);
	add_timer(&mdev->link_stat_timer);
}