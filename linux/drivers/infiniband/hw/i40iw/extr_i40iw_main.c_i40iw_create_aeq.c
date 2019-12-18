#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; TYPE_3__* aeq_ops; TYPE_2__* hmc_info; } ;
struct i40iw_sc_aeqe {int dummy; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;
struct i40iw_aeq {TYPE_4__ mem; int /*<<< orphan*/  sc_aeq; } ;
struct i40iw_device {struct i40iw_sc_dev sc_dev; struct i40iw_aeq aeq; } ;
struct i40iw_aeq_init_info {int elem_cnt; struct i40iw_sc_dev* dev; int /*<<< orphan*/  aeq_elem_pa; int /*<<< orphan*/  aeqe_base; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_8__ {int (* aeq_init ) (int /*<<< orphan*/ *,struct i40iw_aeq_init_info*) ;int (* aeq_create ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int (* aeq_create_done ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__* hmc_obj; } ;
struct TYPE_6__ {int cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_AEQ_ALIGNMENT ; 
 size_t I40IW_HMC_IW_CQ ; 
 size_t I40IW_HMC_IW_QP ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct i40iw_aeq_init_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,struct i40iw_aeq_init_info*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_create_aeq(struct i40iw_device *iwdev)
{
	enum i40iw_status_code status;
	struct i40iw_aeq_init_info info;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_aeq *aeq = &iwdev->aeq;
	u64 scratch = 0;
	u32 aeq_size;

	aeq_size = 2 * iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_QP].cnt +
		iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	memset(&info, 0, sizeof(info));
	aeq->mem.size = sizeof(struct i40iw_sc_aeqe) * aeq_size;
	status = i40iw_allocate_dma_mem(dev->hw, &aeq->mem, aeq->mem.size,
					I40IW_AEQ_ALIGNMENT);
	if (status)
		goto exit;

	info.aeqe_base = aeq->mem.va;
	info.aeq_elem_pa = aeq->mem.pa;
	info.elem_cnt = aeq_size;
	info.dev = dev;
	status = dev->aeq_ops->aeq_init(&aeq->sc_aeq, &info);
	if (status)
		goto exit;
	status = dev->aeq_ops->aeq_create(&aeq->sc_aeq, scratch, 1);
	if (!status)
		status = dev->aeq_ops->aeq_create_done(&aeq->sc_aeq);
exit:
	if (status)
		i40iw_free_dma_mem(dev->hw, &aeq->mem);
	return status;
}