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
struct iser_mem_reg {int dummy; } ;
struct iser_fr_desc {int /*<<< orphan*/  rsc; } ;
struct iser_device {TYPE_3__* reg_ops; } ;
struct iser_data_buf {int dummy; } ;
struct iscsi_iser_task {TYPE_2__* iser_conn; } ;
struct TYPE_6__ {int (* reg_mem ) (struct iscsi_iser_task*,struct iser_data_buf*,int /*<<< orphan*/ *,struct iser_mem_reg*) ;} ;
struct TYPE_4__ {struct iser_device* device; } ;
struct TYPE_5__ {TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int iser_reg_dma (struct iser_device*,struct iser_data_buf*,struct iser_mem_reg*) ; 
 int stub1 (struct iscsi_iser_task*,struct iser_data_buf*,int /*<<< orphan*/ *,struct iser_mem_reg*) ; 

__attribute__((used)) static int
iser_reg_data_sg(struct iscsi_iser_task *task,
		 struct iser_data_buf *mem,
		 struct iser_fr_desc *desc,
		 bool use_dma_key,
		 struct iser_mem_reg *reg)
{
	struct iser_device *device = task->iser_conn->ib_conn.device;

	if (use_dma_key)
		return iser_reg_dma(device, mem, reg);

	return device->reg_ops->reg_mem(task, mem, &desc->rsc, reg);
}