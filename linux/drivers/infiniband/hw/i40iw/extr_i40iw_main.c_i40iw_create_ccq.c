#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct i40iw_sc_dev {int /*<<< orphan*/  hw; TYPE_3__* ccq; TYPE_2__* ccq_ops; } ;
struct i40iw_dma_mem {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;
struct TYPE_9__ {void* back_cq; struct i40iw_sc_dev* dev; } ;
struct TYPE_7__ {int size; } ;
struct i40iw_ccq {TYPE_5__ mem_cq; TYPE_3__ sc_cq; TYPE_1__ shadow_area; } ;
struct i40iw_device {struct i40iw_ccq ccq; struct i40iw_sc_dev sc_dev; } ;
struct i40iw_cqe {int dummy; } ;
struct i40iw_cq_shadow_area {int dummy; } ;
struct i40iw_ccq_init_info {int num_elem; int ceqe_mask; int ceq_id_valid; int shadow_read_threshold; int /*<<< orphan*/  shadow_area_pa; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  cq_pa; int /*<<< orphan*/  cq_base; struct i40iw_sc_dev* dev; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_8__ {int (* ccq_init ) (TYPE_3__*,struct i40iw_ccq_init_info*) ;int (* ccq_create ) (TYPE_3__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQ0_ALIGNMENT ; 
 int /*<<< orphan*/  I40IW_SHADOWAREA_MASK ; 
 int IW_CCQ_SIZE ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int i40iw_obj_aligned_mem (struct i40iw_device*,struct i40iw_dma_mem*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40iw_ccq_init_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_3__*,struct i40iw_ccq_init_info*) ; 
 int stub2 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_create_ccq(struct i40iw_device *iwdev)
{
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_dma_mem mem;
	enum i40iw_status_code status;
	struct i40iw_ccq_init_info info;
	struct i40iw_ccq *ccq = &iwdev->ccq;

	memset(&info, 0, sizeof(info));
	dev->ccq = &ccq->sc_cq;
	dev->ccq->dev = dev;
	info.dev = dev;
	ccq->shadow_area.size = sizeof(struct i40iw_cq_shadow_area);
	ccq->mem_cq.size = sizeof(struct i40iw_cqe) * IW_CCQ_SIZE;
	status = i40iw_allocate_dma_mem(dev->hw, &ccq->mem_cq,
					ccq->mem_cq.size, I40IW_CQ0_ALIGNMENT);
	if (status)
		goto exit;
	status = i40iw_obj_aligned_mem(iwdev, &mem, ccq->shadow_area.size,
				       I40IW_SHADOWAREA_MASK);
	if (status)
		goto exit;
	ccq->sc_cq.back_cq = (void *)ccq;
	/* populate the ccq init info */
	info.cq_base = ccq->mem_cq.va;
	info.cq_pa = ccq->mem_cq.pa;
	info.num_elem = IW_CCQ_SIZE;
	info.shadow_area = mem.va;
	info.shadow_area_pa = mem.pa;
	info.ceqe_mask = false;
	info.ceq_id_valid = true;
	info.shadow_read_threshold = 16;
	status = dev->ccq_ops->ccq_init(dev->ccq, &info);
	if (!status)
		status = dev->ccq_ops->ccq_create(dev->ccq, 0, true, true);
exit:
	if (status)
		i40iw_free_dma_mem(dev->hw, &ccq->mem_cq);
	return status;
}