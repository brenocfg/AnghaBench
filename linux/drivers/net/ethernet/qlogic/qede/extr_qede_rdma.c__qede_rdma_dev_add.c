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
struct TYPE_3__ {int exp_recovery; int /*<<< orphan*/  qedr_dev; } ;
struct qede_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  cdev; TYPE_1__ rdma_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* qedr_drv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _qede_rdma_dev_add(struct qede_dev *edev)
{
	if (!qedr_drv)
		return;

	/* Leftovers from previous error recovery */
	edev->rdma_info.exp_recovery = false;
	edev->rdma_info.qedr_dev = qedr_drv->add(edev->cdev, edev->pdev,
						 edev->ndev);
}