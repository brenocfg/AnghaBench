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
struct TYPE_5__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_destroy_uc {int /*<<< orphan*/  ctx_handle; TYPE_2__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_destroy_uc destroy_uc; } ;
struct pvrdma_ucontext {int /*<<< orphan*/  uar; TYPE_3__* dev; int /*<<< orphan*/  ctx_handle; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVRDMA_CMD_DESTROY_UC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int pvrdma_cmd_post (TYPE_3__*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_uar_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_vdev (int /*<<< orphan*/ ) ; 
 struct pvrdma_ucontext* to_vucontext (struct ib_ucontext*) ; 

void pvrdma_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct pvrdma_ucontext *context = to_vucontext(ibcontext);
	union pvrdma_cmd_req req = {};
	struct pvrdma_cmd_destroy_uc *cmd = &req.destroy_uc;
	int ret;

	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_UC;
	cmd->ctx_handle = context->ctx_handle;

	ret = pvrdma_cmd_post(context->dev, &req, NULL, 0);
	if (ret < 0)
		dev_warn(&context->dev->pdev->dev,
			 "destroy ucontext failed, error: %d\n", ret);

	/* Free the UAR even if the device command failed */
	pvrdma_uar_free(to_vdev(ibcontext->device), &context->uar);
}