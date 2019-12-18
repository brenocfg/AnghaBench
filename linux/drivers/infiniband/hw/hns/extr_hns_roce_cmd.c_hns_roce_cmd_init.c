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
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  max_cmds; scalar_t__ use_events; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  hcr_mutex; } ;
struct hns_roce_dev {TYPE_1__ cmd; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAX_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HNS_ROCE_MAILBOX_SIZE ; 
 int /*<<< orphan*/  dma_pool_create (char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int hns_roce_cmd_init(struct hns_roce_dev *hr_dev)
{
	struct device *dev = hr_dev->dev;

	mutex_init(&hr_dev->cmd.hcr_mutex);
	sema_init(&hr_dev->cmd.poll_sem, 1);
	hr_dev->cmd.use_events = 0;
	hr_dev->cmd.max_cmds = CMD_MAX_NUM;
	hr_dev->cmd.pool = dma_pool_create("hns_roce_cmd", dev,
					   HNS_ROCE_MAILBOX_SIZE,
					   HNS_ROCE_MAILBOX_SIZE, 0);
	if (!hr_dev->cmd.pool)
		return -ENOMEM;

	return 0;
}