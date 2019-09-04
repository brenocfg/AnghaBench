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
struct iser_mem_reg {int /*<<< orphan*/ * mem_h; } ;
struct iser_device {TYPE_2__* reg_ops; } ;
struct iscsi_iser_task {TYPE_1__* iser_conn; struct iser_mem_reg* rdma_reg; } ;
typedef  enum iser_data_dir { ____Placeholder_iser_data_dir } iser_data_dir ;
struct TYPE_6__ {struct iser_device* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reg_desc_put ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_3__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

void iser_unreg_mem_fastreg(struct iscsi_iser_task *iser_task,
			    enum iser_data_dir cmd_dir)
{
	struct iser_device *device = iser_task->iser_conn->ib_conn.device;
	struct iser_mem_reg *reg = &iser_task->rdma_reg[cmd_dir];

	if (!reg->mem_h)
		return;

	device->reg_ops->reg_desc_put(&iser_task->iser_conn->ib_conn,
				     reg->mem_h);
	reg->mem_h = NULL;
}