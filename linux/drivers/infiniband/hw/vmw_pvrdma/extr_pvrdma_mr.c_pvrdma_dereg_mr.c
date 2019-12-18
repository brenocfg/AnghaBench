#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_destroy_mr {int /*<<< orphan*/  mr_handle; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_destroy_mr destroy_mr; } ;
struct TYPE_5__ {int /*<<< orphan*/  mr_handle; } ;
struct pvrdma_user_mr {struct pvrdma_user_mr* pages; int /*<<< orphan*/  umem; int /*<<< orphan*/  pdir; TYPE_2__ mmr; } ;
struct pvrdma_dev {TYPE_3__* pdev; } ;
struct ib_udata {int dummy; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVRDMA_CMD_DESTROY_MR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pvrdma_user_mr*) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_destroy_mr*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,int /*<<< orphan*/ *) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 
 struct pvrdma_user_mr* to_vmr (struct ib_mr*) ; 

int pvrdma_dereg_mr(struct ib_mr *ibmr, struct ib_udata *udata)
{
	struct pvrdma_user_mr *mr = to_vmr(ibmr);
	struct pvrdma_dev *dev = to_vdev(ibmr->device);
	union pvrdma_cmd_req req;
	struct pvrdma_cmd_destroy_mr *cmd = &req.destroy_mr;
	int ret;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_MR;
	cmd->mr_handle = mr->mmr.mr_handle;
	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret < 0)
		dev_warn(&dev->pdev->dev,
			 "could not deregister mem region, error: %d\n", ret);

	pvrdma_page_dir_cleanup(dev, &mr->pdir);
	ib_umem_release(mr->umem);

	kfree(mr->pages);
	kfree(mr);

	return 0;
}