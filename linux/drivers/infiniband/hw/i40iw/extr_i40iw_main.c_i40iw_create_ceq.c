#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t u64 ;
typedef  void* u32 ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; TYPE_4__* ceq_ops; TYPE_2__* hmc_info; } ;
struct TYPE_11__ {int /*<<< orphan*/  sc_cqp; } ;
struct i40iw_device {TYPE_3__ cqp; struct i40iw_sc_dev sc_dev; } ;
struct i40iw_ceqe {int dummy; } ;
struct i40iw_ceq_init_info {int elem_cnt; struct i40iw_sc_dev* dev; int /*<<< orphan*/  ceqe_pa; int /*<<< orphan*/  ceqe_base; void* ceq_id; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;
struct TYPE_13__ {void* ceq_id; } ;
struct i40iw_ceq {TYPE_7__ mem; TYPE_5__ sc_ceq; struct i40iw_device* iwdev; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_12__ {int (* ceq_init ) (TYPE_5__*,struct i40iw_ceq_init_info*) ;int (* cceq_create ) (TYPE_5__*,uintptr_t) ;} ;
struct TYPE_10__ {TYPE_1__* hmc_obj; } ;
struct TYPE_9__ {int cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CEQ_ALIGNMENT ; 
 size_t I40IW_HMC_IW_CQ ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  memset (struct i40iw_ceq_init_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_5__*,struct i40iw_ceq_init_info*) ; 
 int stub2 (TYPE_5__*,uintptr_t) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_create_ceq(struct i40iw_device *iwdev,
					       struct i40iw_ceq *iwceq,
					       u32 ceq_id)
{
	enum i40iw_status_code status;
	struct i40iw_ceq_init_info info;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	u64 scratch;

	memset(&info, 0, sizeof(info));
	info.ceq_id = ceq_id;
	iwceq->iwdev = iwdev;
	iwceq->mem.size = sizeof(struct i40iw_ceqe) *
		iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	status = i40iw_allocate_dma_mem(dev->hw, &iwceq->mem, iwceq->mem.size,
					I40IW_CEQ_ALIGNMENT);
	if (status)
		goto exit;
	info.ceq_id = ceq_id;
	info.ceqe_base = iwceq->mem.va;
	info.ceqe_pa = iwceq->mem.pa;

	info.elem_cnt = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	iwceq->sc_ceq.ceq_id = ceq_id;
	info.dev = dev;
	scratch = (uintptr_t)&iwdev->cqp.sc_cqp;
	status = dev->ceq_ops->ceq_init(&iwceq->sc_ceq, &info);
	if (!status)
		status = dev->ceq_ops->cceq_create(&iwceq->sc_ceq, scratch);

exit:
	if (status)
		i40iw_free_dma_mem(dev->hw, &iwceq->mem);
	return status;
}