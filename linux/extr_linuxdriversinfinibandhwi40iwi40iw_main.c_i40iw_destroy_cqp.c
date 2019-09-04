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
struct i40iw_sc_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  cqp; TYPE_1__* cqp_ops; } ;
struct i40iw_cqp {int /*<<< orphan*/ * cqp_requests; int /*<<< orphan*/ * scratch_array; int /*<<< orphan*/  sq; } ;
struct i40iw_device {struct i40iw_cqp cqp; struct i40iw_sc_dev sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cqp_destroy ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_cleanup_pending_cqp_op (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_destroy_cqp(struct i40iw_device *iwdev, bool free_hwcqp)
{
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_cqp *cqp = &iwdev->cqp;

	if (free_hwcqp)
		dev->cqp_ops->cqp_destroy(dev->cqp);

	i40iw_cleanup_pending_cqp_op(iwdev);

	i40iw_free_dma_mem(dev->hw, &cqp->sq);
	kfree(cqp->scratch_array);
	iwdev->cqp.scratch_array = NULL;

	kfree(cqp->cqp_requests);
	cqp->cqp_requests = NULL;
}