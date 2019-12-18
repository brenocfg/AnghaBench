#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uresp ;
struct pvrdma_cmd_create_uc_resp {int /*<<< orphan*/  ctx_handle; } ;
union pvrdma_cmd_resp {struct pvrdma_cmd_create_uc_resp create_uc_resp; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_create_uc {TYPE_1__ hdr; int /*<<< orphan*/  pfn64; int /*<<< orphan*/  pfn; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_create_uc create_uc; } ;
struct TYPE_11__ {int /*<<< orphan*/  pfn; } ;
struct pvrdma_ucontext {TYPE_5__ uar; int /*<<< orphan*/  ibucontext; int /*<<< orphan*/  ctx_handle; struct pvrdma_dev* dev; } ;
struct pvrdma_dev {scalar_t__ dsr_version; TYPE_4__* dsr; TYPE_2__* pdev; int /*<<< orphan*/  ib_active; } ;
struct pvrdma_alloc_ucontext_resp {int /*<<< orphan*/  qp_tab_size; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {struct ib_device* device; } ;
struct ib_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  max_qp; } ;
struct TYPE_10__ {TYPE_3__ caps; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PVRDMA_CMD_CREATE_UC ; 
 int /*<<< orphan*/  PVRDMA_CMD_CREATE_UC_RESP ; 
 scalar_t__ PVRDMA_PPN64_VERSION ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int ib_copy_to_udata (struct ib_udata*,struct pvrdma_alloc_ucontext_resp*,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,union pvrdma_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_dealloc_ucontext (int /*<<< orphan*/ *) ; 
 int pvrdma_uar_alloc (struct pvrdma_dev*,TYPE_5__*) ; 
 int /*<<< orphan*/  pvrdma_uar_free (struct pvrdma_dev*,TYPE_5__*) ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 
 struct pvrdma_ucontext* to_vucontext (struct ib_ucontext*) ; 

int pvrdma_alloc_ucontext(struct ib_ucontext *uctx, struct ib_udata *udata)
{
	struct ib_device *ibdev = uctx->device;
	struct pvrdma_dev *vdev = to_vdev(ibdev);
	struct pvrdma_ucontext *context = to_vucontext(uctx);
	union pvrdma_cmd_req req = {};
	union pvrdma_cmd_resp rsp = {};
	struct pvrdma_cmd_create_uc *cmd = &req.create_uc;
	struct pvrdma_cmd_create_uc_resp *resp = &rsp.create_uc_resp;
	struct pvrdma_alloc_ucontext_resp uresp = {};
	int ret;

	if (!vdev->ib_active)
		return -EAGAIN;

	context->dev = vdev;
	ret = pvrdma_uar_alloc(vdev, &context->uar);
	if (ret)
		return -ENOMEM;

	/* get ctx_handle from host */
	if (vdev->dsr_version < PVRDMA_PPN64_VERSION)
		cmd->pfn = context->uar.pfn;
	else
		cmd->pfn64 = context->uar.pfn;

	cmd->hdr.cmd = PVRDMA_CMD_CREATE_UC;
	ret = pvrdma_cmd_post(vdev, &req, &rsp, PVRDMA_CMD_CREATE_UC_RESP);
	if (ret < 0) {
		dev_warn(&vdev->pdev->dev,
			 "could not create ucontext, error: %d\n", ret);
		goto err;
	}

	context->ctx_handle = resp->ctx_handle;

	/* copy back to user */
	uresp.qp_tab_size = vdev->dsr->caps.max_qp;
	ret = ib_copy_to_udata(udata, &uresp, sizeof(uresp));
	if (ret) {
		pvrdma_uar_free(vdev, &context->uar);
		pvrdma_dealloc_ucontext(&context->ibucontext);
		return -EFAULT;
	}

	return 0;

err:
	pvrdma_uar_free(vdev, &context->uar);
	return ret;
}