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
struct hnae3_handle {int /*<<< orphan*/  last_reset_time; } ;
struct hclge_dev {int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  reset_type; int /*<<< orphan*/  ae_dev; TYPE_1__* vport; } ;
struct TYPE_2__ {struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 int /*<<< orphan*/  HNAE3_INIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UNINIT_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int /*<<< orphan*/  hclge_clear_reset_cause (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_notify_client (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_ae_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_wait (struct hclge_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_reset(struct hclge_dev *hdev)
{
	struct hnae3_handle *handle;

	/* perform reset of the stack & ae device for a client */
	handle = &hdev->vport[0].nic;
	rtnl_lock();
	hclge_notify_client(hdev, HNAE3_DOWN_CLIENT);
	rtnl_unlock();

	if (!hclge_reset_wait(hdev)) {
		rtnl_lock();
		hclge_notify_client(hdev, HNAE3_UNINIT_CLIENT);
		hclge_reset_ae_dev(hdev->ae_dev);
		hclge_notify_client(hdev, HNAE3_INIT_CLIENT);

		hclge_clear_reset_cause(hdev);
	} else {
		rtnl_lock();
		/* schedule again to check pending resets later */
		set_bit(hdev->reset_type, &hdev->reset_pending);
		hclge_reset_task_schedule(hdev);
	}

	hclge_notify_client(hdev, HNAE3_UP_CLIENT);
	handle->last_reset_time = jiffies;
	rtnl_unlock();
}