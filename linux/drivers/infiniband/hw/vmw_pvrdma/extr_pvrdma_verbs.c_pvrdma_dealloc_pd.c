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
struct pvrdma_cmd_destroy_pd {int /*<<< orphan*/  pd_handle; TYPE_2__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_destroy_pd destroy_pd; } ;
struct pvrdma_dev {int /*<<< orphan*/  num_pds; TYPE_1__* pdev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd_handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVRDMA_CMD_DESTROY_PD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_vpd (struct ib_pd*) ; 

void pvrdma_dealloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	struct pvrdma_dev *dev = to_vdev(pd->device);
	union pvrdma_cmd_req req = {};
	struct pvrdma_cmd_destroy_pd *cmd = &req.destroy_pd;
	int ret;

	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_PD;
	cmd->pd_handle = to_vpd(pd)->pd_handle;

	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret)
		dev_warn(&dev->pdev->dev,
			 "could not dealloc protection domain, error: %d\n",
			 ret);

	atomic_dec(&dev->num_pds);
}