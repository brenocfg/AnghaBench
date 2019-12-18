#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_card {int /*<<< orphan*/  rx_mode_work; int /*<<< orphan*/  ip_mc_htable; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_htable; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
struct ccwgroup_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct qeth_card* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_generic_devtype ; 
 int qeth_l3_create_device_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  qeth_l3_rx_mode_work ; 

__attribute__((used)) static int qeth_l3_probe_device(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	int rc;

	hash_init(card->ip_htable);
	mutex_init(&card->ip_lock);
	card->cmd_wq = alloc_ordered_workqueue("%s_cmd", 0,
					       dev_name(&gdev->dev));
	if (!card->cmd_wq)
		return -ENOMEM;

	if (gdev->dev.type == &qeth_generic_devtype) {
		rc = qeth_l3_create_device_attributes(&gdev->dev);
		if (rc) {
			destroy_workqueue(card->cmd_wq);
			return rc;
		}
	}

	hash_init(card->ip_mc_htable);
	INIT_WORK(&card->rx_mode_work, qeth_l3_rx_mode_work);
	return 0;
}