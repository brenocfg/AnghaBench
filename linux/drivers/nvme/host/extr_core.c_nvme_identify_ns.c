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
struct nvme_id_ns {int dummy; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  admin_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  cns; int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ identify; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_ID_CNS_NS ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_id_ns*) ; 
 struct nvme_id_ns* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_admin_identify ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,struct nvme_id_ns*,int) ; 

__attribute__((used)) static int nvme_identify_ns(struct nvme_ctrl *ctrl,
		unsigned nsid, struct nvme_id_ns **id)
{
	struct nvme_command c = { };
	int error;

	/* gcc-4.4.4 (at least) has issues with initializers and anon unions */
	c.identify.opcode = nvme_admin_identify;
	c.identify.nsid = cpu_to_le32(nsid);
	c.identify.cns = NVME_ID_CNS_NS;

	*id = kmalloc(sizeof(**id), GFP_KERNEL);
	if (!*id)
		return -ENOMEM;

	error = nvme_submit_sync_cmd(ctrl->admin_q, &c, *id, sizeof(**id));
	if (error) {
		dev_warn(ctrl->device, "Identify namespace failed (%d)\n", error);
		kfree(*id);
	}

	return error;
}