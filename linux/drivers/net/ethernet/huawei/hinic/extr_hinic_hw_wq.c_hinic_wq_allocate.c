#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_wqs {struct hinic_hwif* hwif; } ;
struct hinic_wq {int /*<<< orphan*/  block_idx; int /*<<< orphan*/  page_idx; scalar_t__ mask; int /*<<< orphan*/  delta; int /*<<< orphan*/  prod_idx; int /*<<< orphan*/  cons_idx; int /*<<< orphan*/  block_paddr; int /*<<< orphan*/  shadow_block_vaddr; int /*<<< orphan*/  block_vaddr; scalar_t__ wqebb_size_shift; void* wqebbs_per_page_shift; scalar_t__ num_wqebbs_per_page; scalar_t__ max_wqe_size; scalar_t__ q_depth; scalar_t__ wq_page_size; scalar_t__ wqebb_size; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WQ_BASE_ADDR (struct hinic_wqs*,struct hinic_wq*) ; 
 int /*<<< orphan*/  WQ_BASE_PADDR (struct hinic_wqs*,struct hinic_wq*) ; 
 int /*<<< orphan*/  WQ_BASE_VADDR (struct hinic_wqs*,struct hinic_wq*) ; 
 int /*<<< orphan*/  WQ_MAX_PAGES ; 
 int alloc_wq_pages (struct hinic_wq*,struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int wqs_next_block (struct hinic_wqs*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wqs_return_block (struct hinic_wqs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hinic_wq_allocate(struct hinic_wqs *wqs, struct hinic_wq *wq,
		      u16 wqebb_size, u16 wq_page_size, u16 q_depth,
		      u16 max_wqe_size)
{
	struct hinic_hwif *hwif = wqs->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 num_wqebbs_per_page;
	u16 wqebb_size_shift;
	int err;

	if (!is_power_of_2(wqebb_size)) {
		dev_err(&pdev->dev, "wqebb_size must be power of 2\n");
		return -EINVAL;
	}

	if (wq_page_size == 0) {
		dev_err(&pdev->dev, "wq_page_size must be > 0\n");
		return -EINVAL;
	}

	if (q_depth & (q_depth - 1)) {
		dev_err(&pdev->dev, "WQ q_depth must be power of 2\n");
		return -EINVAL;
	}

	wqebb_size_shift = ilog2(wqebb_size);
	num_wqebbs_per_page = ALIGN(wq_page_size, wqebb_size)
				>> wqebb_size_shift;

	if (!is_power_of_2(num_wqebbs_per_page)) {
		dev_err(&pdev->dev, "num wqebbs per page must be power of 2\n");
		return -EINVAL;
	}

	wq->hwif = hwif;

	err = wqs_next_block(wqs, &wq->page_idx, &wq->block_idx);
	if (err) {
		dev_err(&pdev->dev, "Failed to get free wqs next block\n");
		return err;
	}

	wq->wqebb_size = wqebb_size;
	wq->wq_page_size = wq_page_size;
	wq->q_depth = q_depth;
	wq->max_wqe_size = max_wqe_size;
	wq->num_wqebbs_per_page = num_wqebbs_per_page;
	wq->wqebbs_per_page_shift = ilog2(num_wqebbs_per_page);
	wq->wqebb_size_shift = wqebb_size_shift;
	wq->block_vaddr = WQ_BASE_VADDR(wqs, wq);
	wq->shadow_block_vaddr = WQ_BASE_ADDR(wqs, wq);
	wq->block_paddr = WQ_BASE_PADDR(wqs, wq);

	err = alloc_wq_pages(wq, wqs->hwif, WQ_MAX_PAGES);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate wq pages\n");
		goto err_alloc_wq_pages;
	}

	atomic_set(&wq->cons_idx, 0);
	atomic_set(&wq->prod_idx, 0);
	atomic_set(&wq->delta, q_depth);
	wq->mask = q_depth - 1;

	return 0;

err_alloc_wq_pages:
	wqs_return_block(wqs, wq->page_idx, wq->block_idx);
	return err;
}