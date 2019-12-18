#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qeth_card {int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  close_dev_work; int /*<<< orphan*/  wait_q; } ;
struct TYPE_3__ {int /*<<< orphan*/ * type; } ;
struct ccwgroup_device {scalar_t__ state; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct qeth_card* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_generic_devtype ; 
 int /*<<< orphan*/  qeth_l3_clear_ip_htable (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_clear_ipato_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_remove_device_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  qeth_l3_set_offline (struct ccwgroup_device*) ; 
 scalar_t__ qeth_netdev_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_threads_running (struct qeth_card*,int) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qeth_l3_remove_device(struct ccwgroup_device *cgdev)
{
	struct qeth_card *card = dev_get_drvdata(&cgdev->dev);

	if (cgdev->dev.type == &qeth_generic_devtype)
		qeth_l3_remove_device_attributes(&cgdev->dev);

	qeth_set_allowed_threads(card, 0, 1);
	wait_event(card->wait_q, qeth_threads_running(card, 0xffffffff) == 0);

	if (cgdev->state == CCWGROUP_ONLINE)
		qeth_l3_set_offline(cgdev);

	cancel_work_sync(&card->close_dev_work);
	if (qeth_netdev_is_registered(card->dev))
		unregister_netdev(card->dev);

	flush_workqueue(card->cmd_wq);
	destroy_workqueue(card->cmd_wq);
	qeth_l3_clear_ip_htable(card, 0);
	qeth_l3_clear_ipato_list(card);
}