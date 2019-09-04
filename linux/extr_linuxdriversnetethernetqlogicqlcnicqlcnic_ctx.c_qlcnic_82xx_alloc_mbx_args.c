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
struct qlcnic_mailbox_metadata {scalar_t__ cmd; int /*<<< orphan*/  out_args; int /*<<< orphan*/  in_args; } ;
struct TYPE_4__ {scalar_t__* arg; int /*<<< orphan*/  num; } ;
struct TYPE_3__ {void* arg; int /*<<< orphan*/  num; } ;
struct qlcnic_cmd_args {TYPE_2__ req; TYPE_1__ rsp; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qlcnic_mailbox_metadata*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 struct qlcnic_mailbox_metadata* qlcnic_mbx_tbl ; 

int qlcnic_82xx_alloc_mbx_args(struct qlcnic_cmd_args *mbx,
			       struct qlcnic_adapter *adapter, u32 type)
{
	int i, size;
	const struct qlcnic_mailbox_metadata *mbx_tbl;

	mbx_tbl = qlcnic_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_mbx_tbl);
	for (i = 0; i < size; i++) {
		if (type == mbx_tbl[i].cmd) {
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kcalloc(mbx->req.num,
					       sizeof(u32), GFP_ATOMIC);
			if (!mbx->req.arg)
				return -ENOMEM;
			mbx->rsp.arg = kcalloc(mbx->rsp.num,
					       sizeof(u32), GFP_ATOMIC);
			if (!mbx->rsp.arg) {
				kfree(mbx->req.arg);
				mbx->req.arg = NULL;
				return -ENOMEM;
			}
			mbx->req.arg[0] = type;
			break;
		}
	}
	return 0;
}