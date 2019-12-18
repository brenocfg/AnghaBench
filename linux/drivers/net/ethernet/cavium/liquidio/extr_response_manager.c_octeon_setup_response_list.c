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
struct TYPE_6__ {struct octeon_device* ctxptr; int /*<<< orphan*/  work; } ;
struct cavium_wq {TYPE_3__ wk; int /*<<< orphan*/  wq; } ;
struct octeon_device {int /*<<< orphan*/  cmd_resp_state; struct cavium_wq dma_comp_wq; TYPE_2__* pci_dev; int /*<<< orphan*/  cmd_resp_wqlock; TYPE_1__* response_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_req_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_RESPONSE_LISTS ; 
 int /*<<< orphan*/  OCT_DRV_ONLINE ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  oct_poll_req_completion ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int octeon_setup_response_list(struct octeon_device *oct)
{
	int i, ret = 0;
	struct cavium_wq *cwq;

	for (i = 0; i < MAX_RESPONSE_LISTS; i++) {
		INIT_LIST_HEAD(&oct->response_list[i].head);
		spin_lock_init(&oct->response_list[i].lock);
		atomic_set(&oct->response_list[i].pending_req_count, 0);
	}
	spin_lock_init(&oct->cmd_resp_wqlock);

	oct->dma_comp_wq.wq = alloc_workqueue("dma-comp", WQ_MEM_RECLAIM, 0);
	if (!oct->dma_comp_wq.wq) {
		dev_err(&oct->pci_dev->dev, "failed to create wq thread\n");
		return -ENOMEM;
	}

	cwq = &oct->dma_comp_wq;
	INIT_DELAYED_WORK(&cwq->wk.work, oct_poll_req_completion);
	cwq->wk.ctxptr = oct;
	oct->cmd_resp_state = OCT_DRV_ONLINE;

	return ret;
}