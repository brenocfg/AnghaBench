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
struct se_device {int dummy; } ;
struct tcmu_dev {int qfull_time_out; struct se_device se_dev; int /*<<< orphan*/  data_blocks; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  qfull_timer; int /*<<< orphan*/  commands; int /*<<< orphan*/  inflight_queue; int /*<<< orphan*/  qfull_queue; int /*<<< orphan*/  timedout_entry; int /*<<< orphan*/  node; int /*<<< orphan*/  cmdr_lock; int /*<<< orphan*/  max_blocks; int /*<<< orphan*/  cmd_time_out; struct se_hba* hba; int /*<<< orphan*/  name; int /*<<< orphan*/  kref; } ;
struct se_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_BLOCK_BITS_DEF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCMU_TIME_OUT ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcmu_dev*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct tcmu_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcmu_cmd_timedout ; 
 int /*<<< orphan*/  tcmu_qfull_timedout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct se_device *tcmu_alloc_device(struct se_hba *hba, const char *name)
{
	struct tcmu_dev *udev;

	udev = kzalloc(sizeof(struct tcmu_dev), GFP_KERNEL);
	if (!udev)
		return NULL;
	kref_init(&udev->kref);

	udev->name = kstrdup(name, GFP_KERNEL);
	if (!udev->name) {
		kfree(udev);
		return NULL;
	}

	udev->hba = hba;
	udev->cmd_time_out = TCMU_TIME_OUT;
	udev->qfull_time_out = -1;

	udev->max_blocks = DATA_BLOCK_BITS_DEF;
	mutex_init(&udev->cmdr_lock);

	INIT_LIST_HEAD(&udev->node);
	INIT_LIST_HEAD(&udev->timedout_entry);
	INIT_LIST_HEAD(&udev->qfull_queue);
	INIT_LIST_HEAD(&udev->inflight_queue);
	idr_init(&udev->commands);

	timer_setup(&udev->qfull_timer, tcmu_qfull_timedout, 0);
	timer_setup(&udev->cmd_timer, tcmu_cmd_timedout, 0);

	INIT_RADIX_TREE(&udev->data_blocks, GFP_KERNEL);

	return &udev->se_dev;
}