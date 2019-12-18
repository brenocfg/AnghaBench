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
struct TYPE_2__ {int /*<<< orphan*/  rdma_wq; int /*<<< orphan*/  rdma_event_list; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 

__attribute__((used)) static int qede_rdma_create_wq(struct qede_dev *edev)
{
	INIT_LIST_HEAD(&edev->rdma_info.rdma_event_list);
	edev->rdma_info.rdma_wq = create_singlethread_workqueue("rdma_wq");
	if (!edev->rdma_info.rdma_wq) {
		DP_NOTICE(edev, "qedr: Could not create workqueue\n");
		return -ENOMEM;
	}

	return 0;
}