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
struct TYPE_2__ {int /*<<< orphan*/  stats_timer; } ;
struct hclge_dev {TYPE_1__ hw_stats; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 struct hclge_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_task_schedule (struct hclge_dev*) ; 
 struct hclge_dev* hdev ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void hclge_service_timer(struct timer_list *t)
{
	struct hclge_dev *hdev = from_timer(hdev, t, service_timer);

	mod_timer(&hdev->service_timer, jiffies + HZ);
	hdev->hw_stats.stats_timer++;
	hclge_task_schedule(hdev);
}