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
typedef  int /*<<< orphan*/  u8 ;
struct request_queue {struct nvme_ns* queuedata; } ;
struct ppa_addr {int /*<<< orphan*/  ppa; } ;
struct TYPE_4__ {int /*<<< orphan*/  spba; int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_nvm_command {TYPE_2__ get_bb; } ;
struct nvme_nvm_bb_tbl {char* tblid; int /*<<< orphan*/  blk; int /*<<< orphan*/  tblks; int /*<<< orphan*/  verid; } ;
struct nvme_ns {TYPE_1__* head; struct nvme_ctrl* ctrl; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  admin_q; } ;
struct nvme_command {int dummy; } ;
struct nvm_geo {int num_chk; int num_pln; } ;
struct nvm_dev {struct nvm_geo geo; struct request_queue* q; } ;
struct TYPE_3__ {int /*<<< orphan*/  ns_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct nvme_nvm_bb_tbl*) ; 
 struct nvme_nvm_bb_tbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_nvm_admin_get_bb_tbl ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,struct nvme_nvm_bb_tbl*,int) ; 

__attribute__((used)) static int nvme_nvm_get_bb_tbl(struct nvm_dev *nvmdev, struct ppa_addr ppa,
								u8 *blks)
{
	struct request_queue *q = nvmdev->q;
	struct nvm_geo *geo = &nvmdev->geo;
	struct nvme_ns *ns = q->queuedata;
	struct nvme_ctrl *ctrl = ns->ctrl;
	struct nvme_nvm_command c = {};
	struct nvme_nvm_bb_tbl *bb_tbl;
	int nr_blks = geo->num_chk * geo->num_pln;
	int tblsz = sizeof(struct nvme_nvm_bb_tbl) + nr_blks;
	int ret = 0;

	c.get_bb.opcode = nvme_nvm_admin_get_bb_tbl;
	c.get_bb.nsid = cpu_to_le32(ns->head->ns_id);
	c.get_bb.spba = cpu_to_le64(ppa.ppa);

	bb_tbl = kzalloc(tblsz, GFP_KERNEL);
	if (!bb_tbl)
		return -ENOMEM;

	ret = nvme_submit_sync_cmd(ctrl->admin_q, (struct nvme_command *)&c,
								bb_tbl, tblsz);
	if (ret) {
		dev_err(ctrl->device, "get bad block table failed (%d)\n", ret);
		ret = -EIO;
		goto out;
	}

	if (bb_tbl->tblid[0] != 'B' || bb_tbl->tblid[1] != 'B' ||
		bb_tbl->tblid[2] != 'L' || bb_tbl->tblid[3] != 'T') {
		dev_err(ctrl->device, "bbt format mismatch\n");
		ret = -EINVAL;
		goto out;
	}

	if (le16_to_cpu(bb_tbl->verid) != 1) {
		ret = -EINVAL;
		dev_err(ctrl->device, "bbt version not supported\n");
		goto out;
	}

	if (le32_to_cpu(bb_tbl->tblks) != nr_blks) {
		ret = -EINVAL;
		dev_err(ctrl->device,
				"bbt unsuspected blocks returned (%u!=%u)",
				le32_to_cpu(bb_tbl->tblks), nr_blks);
		goto out;
	}

	memcpy(blks, bb_tbl->blk, geo->num_chk * geo->num_pln);
out:
	kfree(bb_tbl);
	return ret;
}