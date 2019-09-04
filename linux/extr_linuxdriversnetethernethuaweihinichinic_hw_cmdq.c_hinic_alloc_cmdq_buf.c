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
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_cmdqs {int /*<<< orphan*/  cmdq_buf_pool; struct hinic_hwif* hwif; } ;
struct hinic_cmdq_buf {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hinic_alloc_cmdq_buf(struct hinic_cmdqs *cmdqs,
			 struct hinic_cmdq_buf *cmdq_buf)
{
	struct hinic_hwif *hwif = cmdqs->hwif;
	struct pci_dev *pdev = hwif->pdev;

	cmdq_buf->buf = dma_pool_alloc(cmdqs->cmdq_buf_pool, GFP_KERNEL,
				       &cmdq_buf->dma_addr);
	if (!cmdq_buf->buf) {
		dev_err(&pdev->dev, "Failed to allocate cmd from the pool\n");
		return -ENOMEM;
	}

	return 0;
}