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
struct TYPE_2__ {int /*<<< orphan*/  rdma_wq; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_rdma_cleanup_event (struct qede_dev*) ; 

__attribute__((used)) static void qede_rdma_destroy_wq(struct qede_dev *edev)
{
	qede_rdma_cleanup_event(edev);
	destroy_workqueue(edev->rdma_info.rdma_wq);
}