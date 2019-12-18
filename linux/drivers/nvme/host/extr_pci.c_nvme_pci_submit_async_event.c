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
struct nvme_queue {int dummy; } ;
struct nvme_dev {struct nvme_queue* queues; } ;
struct nvme_ctrl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  command_id; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_AQ_BLK_MQ_DEPTH ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_async_event ; 
 int /*<<< orphan*/  nvme_submit_cmd (struct nvme_queue*,struct nvme_command*,int) ; 
 struct nvme_dev* to_nvme_dev (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_pci_submit_async_event(struct nvme_ctrl *ctrl)
{
	struct nvme_dev *dev = to_nvme_dev(ctrl);
	struct nvme_queue *nvmeq = &dev->queues[0];
	struct nvme_command c;

	memset(&c, 0, sizeof(c));
	c.common.opcode = nvme_admin_async_event;
	c.common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	nvme_submit_cmd(nvmeq, &c, true);
}