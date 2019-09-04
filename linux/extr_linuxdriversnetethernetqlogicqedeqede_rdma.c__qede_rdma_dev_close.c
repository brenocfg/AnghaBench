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
struct TYPE_3__ {scalar_t__ qedr_dev; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* notify ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDE_DOWN ; 
 TYPE_2__* qedr_drv ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _qede_rdma_dev_close(struct qede_dev *edev)
{
	if (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notify)
		qedr_drv->notify(edev->rdma_info.qedr_dev, QEDE_DOWN);
}