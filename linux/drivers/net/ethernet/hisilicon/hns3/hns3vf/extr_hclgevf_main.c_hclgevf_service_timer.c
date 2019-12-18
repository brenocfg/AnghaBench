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
struct hclgevf_dev {int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 int HCLGEVF_GENERAL_TASK_INTERVAL ; 
 int HZ ; 
 struct hclgevf_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_task_schedule (struct hclgevf_dev*) ; 
 struct hclgevf_dev* hdev ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void hclgevf_service_timer(struct timer_list *t)
{
	struct hclgevf_dev *hdev = from_timer(hdev, t, service_timer);

	mod_timer(&hdev->service_timer, jiffies +
		  HCLGEVF_GENERAL_TASK_INTERVAL * HZ);

	hdev->stats_timer++;
	hclgevf_task_schedule(hdev);
}