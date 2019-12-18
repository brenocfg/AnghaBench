#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  device; int /*<<< orphan*/  admin_q; } ;
struct nvme_dev {TYPE_1__ ctrl; int /*<<< orphan*/  dbbuf_eis_dma_addr; int /*<<< orphan*/  dbbuf_dbs_dma_addr; int /*<<< orphan*/  dbbuf_dbs; } ;
struct TYPE_4__ {void* prp2; void* prp1; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_2__ dbbuf; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_dbbuf ; 
 int /*<<< orphan*/  nvme_dbbuf_dma_free (struct nvme_dev*) ; 
 scalar_t__ nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_dbbuf_set(struct nvme_dev *dev)
{
	struct nvme_command c;

	if (!dev->dbbuf_dbs)
		return;

	memset(&c, 0, sizeof(c));
	c.dbbuf.opcode = nvme_admin_dbbuf;
	c.dbbuf.prp1 = cpu_to_le64(dev->dbbuf_dbs_dma_addr);
	c.dbbuf.prp2 = cpu_to_le64(dev->dbbuf_eis_dma_addr);

	if (nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, NULL, 0)) {
		dev_warn(dev->ctrl.device, "unable to set dbbuf\n");
		/* Free memory and continue on */
		nvme_dbbuf_dma_free(dev);
	}
}