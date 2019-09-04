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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * wrid_mem; int /*<<< orphan*/  dma_mem; } ;
struct i40iw_pbl {int /*<<< orphan*/  pble_alloc; scalar_t__ pbl_allocated; } ;
struct i40iw_qp {int /*<<< orphan*/ * allocated_buffer; TYPE_3__ kqp; int /*<<< orphan*/  q2_ctx_mem; int /*<<< orphan*/  sc_qp; struct i40iw_pbl iwpbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  ieq; } ;
struct i40iw_device {TYPE_2__ sc_dev; int /*<<< orphan*/  pble_rsrc; int /*<<< orphan*/  allocated_qps; TYPE_1__ vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_dealloc_push_page (struct i40iw_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_pble (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_resource (struct i40iw_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i40iw_ieq_cleanup_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void i40iw_free_qp_resources(struct i40iw_device *iwdev,
			     struct i40iw_qp *iwqp,
			     u32 qp_num)
{
	struct i40iw_pbl *iwpbl = &iwqp->iwpbl;

	i40iw_ieq_cleanup_qp(iwdev->vsi.ieq, &iwqp->sc_qp);
	i40iw_dealloc_push_page(iwdev, &iwqp->sc_qp);
	if (qp_num)
		i40iw_free_resource(iwdev, iwdev->allocated_qps, qp_num);
	if (iwpbl->pbl_allocated)
		i40iw_free_pble(iwdev->pble_rsrc, &iwpbl->pble_alloc);
	i40iw_free_dma_mem(iwdev->sc_dev.hw, &iwqp->q2_ctx_mem);
	i40iw_free_dma_mem(iwdev->sc_dev.hw, &iwqp->kqp.dma_mem);
	kfree(iwqp->kqp.wrid_mem);
	iwqp->kqp.wrid_mem = NULL;
	kfree(iwqp->allocated_buffer);
}