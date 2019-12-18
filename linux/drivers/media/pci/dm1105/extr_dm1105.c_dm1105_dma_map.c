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
struct dm1105_dev {int /*<<< orphan*/  ts_buf; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int DM1105_DMA_BYTES ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm1105_dma_map(struct dm1105_dev *dev)
{
	dev->ts_buf = pci_alloc_consistent(dev->pdev,
					6 * DM1105_DMA_BYTES,
					&dev->dma_addr);

	return !dev->ts_buf;
}