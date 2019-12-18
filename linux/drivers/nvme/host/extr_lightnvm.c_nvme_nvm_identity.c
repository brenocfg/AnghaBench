#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvme_nvm_id20 {int dummy; } ;
struct nvme_nvm_id12 {int ver_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_nvm_command {TYPE_2__ identity; } ;
struct nvme_ns {TYPE_4__* ctrl; TYPE_3__* head; } ;
struct nvme_command {int dummy; } ;
struct nvm_dev {int /*<<< orphan*/  geo; TYPE_1__* q; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; int /*<<< orphan*/  admin_q; } ;
struct TYPE_7__ {int /*<<< orphan*/  ns_id; } ;
struct TYPE_5__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_nvm_id12*) ; 
 struct nvme_nvm_id12* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_nvm_admin_identity ; 
 int nvme_nvm_setup_12 (struct nvme_nvm_id12*,int /*<<< orphan*/ *) ; 
 int nvme_nvm_setup_20 (struct nvme_nvm_id20*,int /*<<< orphan*/ *) ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,struct nvme_nvm_id12*,int) ; 

__attribute__((used)) static int nvme_nvm_identity(struct nvm_dev *nvmdev)
{
	struct nvme_ns *ns = nvmdev->q->queuedata;
	struct nvme_nvm_id12 *id;
	struct nvme_nvm_command c = {};
	int ret;

	c.identity.opcode = nvme_nvm_admin_identity;
	c.identity.nsid = cpu_to_le32(ns->head->ns_id);

	id = kmalloc(sizeof(struct nvme_nvm_id12), GFP_KERNEL);
	if (!id)
		return -ENOMEM;

	ret = nvme_submit_sync_cmd(ns->ctrl->admin_q, (struct nvme_command *)&c,
				id, sizeof(struct nvme_nvm_id12));
	if (ret) {
		ret = -EIO;
		goto out;
	}

	/*
	 * The 1.2 and 2.0 specifications share the first byte in their geometry
	 * command to make it possible to know what version a device implements.
	 */
	switch (id->ver_id) {
	case 1:
		ret = nvme_nvm_setup_12(id, &nvmdev->geo);
		break;
	case 2:
		ret = nvme_nvm_setup_20((struct nvme_nvm_id20 *)id,
							&nvmdev->geo);
		break;
	default:
		dev_err(ns->ctrl->device, "OCSSD revision not supported (%d)\n",
							id->ver_id);
		ret = -EINVAL;
	}

out:
	kfree(id);
	return ret;
}