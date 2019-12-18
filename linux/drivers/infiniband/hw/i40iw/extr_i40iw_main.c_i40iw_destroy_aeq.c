#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i40iw_sc_dev {int /*<<< orphan*/  hw; TYPE_1__* aeq_ops; } ;
struct i40iw_aeq {int /*<<< orphan*/  mem; int /*<<< orphan*/  sc_aeq; } ;
struct i40iw_device {scalar_t__ reset; int /*<<< orphan*/  iw_msixtbl; int /*<<< orphan*/  msix_shared; struct i40iw_aeq aeq; struct i40iw_sc_dev sc_dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int (* aeq_destroy_done ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* aeq_destroy ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int I40IW_ERR_NOT_READY ; 
 int /*<<< orphan*/  i40iw_disable_irq (struct i40iw_sc_dev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_destroy_aeq(struct i40iw_device *iwdev)
{
	enum i40iw_status_code status = I40IW_ERR_NOT_READY;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_aeq *aeq = &iwdev->aeq;

	if (!iwdev->msix_shared)
		i40iw_disable_irq(dev, iwdev->iw_msixtbl, (void *)iwdev);
	if (iwdev->reset)
		goto exit;

	if (!dev->aeq_ops->aeq_destroy(&aeq->sc_aeq, 0, 1))
		status = dev->aeq_ops->aeq_destroy_done(&aeq->sc_aeq);
	if (status)
		i40iw_pr_err("destroy aeq failed %d\n", status);

exit:
	i40iw_free_dma_mem(dev->hw, &aeq->mem);
}