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
typedef  scalar_t__ u32 ;
struct qlcnic_mailbox_metadata {scalar_t__ cmd; int in_args; int out_args; } ;
struct TYPE_4__ {int num; scalar_t__* arg; } ;
struct TYPE_3__ {int num; scalar_t__* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; int /*<<< orphan*/  op_type; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qlcnic_mailbox_metadata*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QLC_BC_CMD ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 struct qlcnic_mailbox_metadata* qlcnic_sriov_bc_mbx_tbl ; 

__attribute__((used)) static int qlcnic_sriov_alloc_bc_mbx_args(struct qlcnic_cmd_args *mbx, u32 type)
{
	const struct qlcnic_mailbox_metadata *mbx_tbl;
	int i, size;

	mbx_tbl = qlcnic_sriov_bc_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_sriov_bc_mbx_tbl);

	for (i = 0; i < size; i++) {
		if (type == mbx_tbl[i].cmd) {
			mbx->op_type = QLC_BC_CMD;
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kcalloc(mbx->req.num, sizeof(u32),
					       GFP_ATOMIC);
			if (!mbx->req.arg)
				return -ENOMEM;
			mbx->rsp.arg = kcalloc(mbx->rsp.num, sizeof(u32),
					       GFP_ATOMIC);
			if (!mbx->rsp.arg) {
				kfree(mbx->req.arg);
				mbx->req.arg = NULL;
				return -ENOMEM;
			}
			mbx->req.arg[0] = (type | (mbx->req.num << 16) |
					   (3 << 29));
			mbx->rsp.arg[0] = (type & 0xffff) | mbx->rsp.num << 16;
			return 0;
		}
	}
	return -EINVAL;
}