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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_wqs {int num_pages; int /*<<< orphan*/  free_blocks; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WQS_BLOCKS_PER_PAGE ; 
 int /*<<< orphan*/  WQS_FREE_BLOCKS_SIZE (struct hinic_wqs*) ; 
 int WQS_MAX_NUM_BLOCKS ; 
 scalar_t__ alloc_page_arrays (struct hinic_wqs*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page_arrays (struct hinic_wqs*) ; 
 int /*<<< orphan*/  init_wqs_blocks_arr (struct hinic_wqs*) ; 
 int wqs_allocate_page (struct hinic_wqs*,int) ; 
 int /*<<< orphan*/  wqs_free_page (struct hinic_wqs*,int) ; 

int hinic_wqs_alloc(struct hinic_wqs *wqs, int max_wqs,
		    struct hinic_hwif *hwif)
{
	struct pci_dev *pdev = hwif->pdev;
	int err, i, page_idx;

	max_wqs = ALIGN(max_wqs, WQS_BLOCKS_PER_PAGE);
	if (max_wqs > WQS_MAX_NUM_BLOCKS)  {
		dev_err(&pdev->dev, "Invalid max_wqs = %d\n", max_wqs);
		return -EINVAL;
	}

	wqs->hwif = hwif;
	wqs->num_pages = max_wqs / WQS_BLOCKS_PER_PAGE;

	if (alloc_page_arrays(wqs)) {
		dev_err(&pdev->dev,
			"Failed to allocate mem for page addresses\n");
		return -ENOMEM;
	}

	for (page_idx = 0; page_idx < wqs->num_pages; page_idx++) {
		err = wqs_allocate_page(wqs, page_idx);
		if (err) {
			dev_err(&pdev->dev, "Failed wq page allocation\n");
			goto err_wq_allocate_page;
		}
	}

	wqs->free_blocks = devm_kzalloc(&pdev->dev, WQS_FREE_BLOCKS_SIZE(wqs),
					GFP_KERNEL);
	if (!wqs->free_blocks) {
		err = -ENOMEM;
		goto err_alloc_blocks;
	}

	init_wqs_blocks_arr(wqs);
	return 0;

err_alloc_blocks:
err_wq_allocate_page:
	for (i = 0; i < page_idx; i++)
		wqs_free_page(wqs, i);

	free_page_arrays(wqs);
	return err;
}