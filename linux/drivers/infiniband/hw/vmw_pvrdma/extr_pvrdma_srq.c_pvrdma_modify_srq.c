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
struct TYPE_5__ {int /*<<< orphan*/  srq_limit; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_modify_srq {int attr_mask; TYPE_2__ attrs; int /*<<< orphan*/  srq_handle; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_modify_srq modify_srq; } ;
struct pvrdma_srq {int /*<<< orphan*/  srq_handle; } ;
struct pvrdma_dev {TYPE_3__* pdev; } ;
struct ib_udata {int dummy; } ;
struct ib_srq_attr {int /*<<< orphan*/  srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SRQ_LIMIT ; 
 int /*<<< orphan*/  PVRDMA_CMD_MODIFY_SRQ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_modify_srq*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 
 struct pvrdma_srq* to_vsrq (struct ib_srq*) ; 

int pvrdma_modify_srq(struct ib_srq *ibsrq, struct ib_srq_attr *attr,
		      enum ib_srq_attr_mask attr_mask, struct ib_udata *udata)
{
	struct pvrdma_srq *vsrq = to_vsrq(ibsrq);
	union pvrdma_cmd_req req;
	struct pvrdma_cmd_modify_srq *cmd = &req.modify_srq;
	struct pvrdma_dev *dev = to_vdev(ibsrq->device);
	int ret;

	/* Only support SRQ limit. */
	if (!(attr_mask & IB_SRQ_LIMIT))
		return -EINVAL;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_MODIFY_SRQ;
	cmd->srq_handle = vsrq->srq_handle;
	cmd->attrs.srq_limit = attr->srq_limit;
	cmd->attr_mask = attr_mask;

	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret < 0) {
		dev_warn(&dev->pdev->dev,
			 "could not modify shared receive queue, error: %d\n",
			 ret);

		return -EINVAL;
	}

	return ret;
}