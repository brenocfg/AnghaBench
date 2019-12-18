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
struct lancer_cmd_req_pport_stats {int dummy; } ;
struct device {int dummy; } ;
struct be_mcc_mailbox {int dummy; } ;
struct be_dma_mem {int size; void* dma; void* va; } ;
struct be_cmd_req_rx_filter {int dummy; } ;
struct be_cmd_req_get_stats_v2 {int dummy; } ;
struct be_cmd_req_get_stats_v1 {int dummy; } ;
struct be_cmd_req_get_stats_v0 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_detection_work; scalar_t__ resched_delay; int /*<<< orphan*/  recovery_state; } ;
struct be_adapter {int rx_fc; int tx_fc; int be_get_temp_freq; int /*<<< orphan*/  vxlan_port_list; TYPE_1__ error_recovery; int /*<<< orphan*/  work; TYPE_2__* pdev; int /*<<< orphan*/  et_cmd_compl; int /*<<< orphan*/  mcc_cq_lock; int /*<<< orphan*/  rx_filter_lock; int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  mbox_lock; struct be_dma_mem stats_cmd; struct be_dma_mem rx_filter; struct be_dma_mem mbox_mem; struct be_dma_mem mbox_mem_alloced; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_RECOVERY_ST_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* PTR_ALIGN (void*,int) ; 
 int /*<<< orphan*/  be_err_detection_task ; 
 int /*<<< orphan*/  be_worker ; 
 void* dma_alloc_coherent (struct device*,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,void*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_state (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int be_drv_init(struct be_adapter *adapter)
{
	struct be_dma_mem *mbox_mem_alloc = &adapter->mbox_mem_alloced;
	struct be_dma_mem *mbox_mem_align = &adapter->mbox_mem;
	struct be_dma_mem *rx_filter = &adapter->rx_filter;
	struct be_dma_mem *stats_cmd = &adapter->stats_cmd;
	struct device *dev = &adapter->pdev->dev;
	int status = 0;

	mbox_mem_alloc->size = sizeof(struct be_mcc_mailbox) + 16;
	mbox_mem_alloc->va = dma_alloc_coherent(dev, mbox_mem_alloc->size,
						&mbox_mem_alloc->dma,
						GFP_KERNEL);
	if (!mbox_mem_alloc->va)
		return -ENOMEM;

	mbox_mem_align->size = sizeof(struct be_mcc_mailbox);
	mbox_mem_align->va = PTR_ALIGN(mbox_mem_alloc->va, 16);
	mbox_mem_align->dma = PTR_ALIGN(mbox_mem_alloc->dma, 16);

	rx_filter->size = sizeof(struct be_cmd_req_rx_filter);
	rx_filter->va = dma_alloc_coherent(dev, rx_filter->size,
					   &rx_filter->dma, GFP_KERNEL);
	if (!rx_filter->va) {
		status = -ENOMEM;
		goto free_mbox;
	}

	if (lancer_chip(adapter))
		stats_cmd->size = sizeof(struct lancer_cmd_req_pport_stats);
	else if (BE2_chip(adapter))
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v0);
	else if (BE3_chip(adapter))
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v1);
	else
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v2);
	stats_cmd->va = dma_alloc_coherent(dev, stats_cmd->size,
					   &stats_cmd->dma, GFP_KERNEL);
	if (!stats_cmd->va) {
		status = -ENOMEM;
		goto free_rx_filter;
	}

	mutex_init(&adapter->mbox_lock);
	mutex_init(&adapter->mcc_lock);
	mutex_init(&adapter->rx_filter_lock);
	spin_lock_init(&adapter->mcc_cq_lock);
	init_completion(&adapter->et_cmd_compl);

	pci_save_state(adapter->pdev);

	INIT_DELAYED_WORK(&adapter->work, be_worker);

	adapter->error_recovery.recovery_state = ERR_RECOVERY_ST_NONE;
	adapter->error_recovery.resched_delay = 0;
	INIT_DELAYED_WORK(&adapter->error_recovery.err_detection_work,
			  be_err_detection_task);

	adapter->rx_fc = true;
	adapter->tx_fc = true;

	/* Must be a power of 2 or else MODULO will BUG_ON */
	adapter->be_get_temp_freq = 64;

	INIT_LIST_HEAD(&adapter->vxlan_port_list);
	return 0;

free_rx_filter:
	dma_free_coherent(dev, rx_filter->size, rx_filter->va, rx_filter->dma);
free_mbox:
	dma_free_coherent(dev, mbox_mem_alloc->size, mbox_mem_alloc->va,
			  mbox_mem_alloc->dma);
	return status;
}