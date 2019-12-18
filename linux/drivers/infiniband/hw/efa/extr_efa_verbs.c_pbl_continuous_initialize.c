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
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; } ;
struct TYPE_5__ {TYPE_1__ continuous; } ;
struct pbl_context {int /*<<< orphan*/  pbl_buf_size_in_bytes; TYPE_2__ phys; int /*<<< orphan*/  pbl_buf; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; TYPE_3__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int pbl_continuous_initialize(struct efa_dev *dev,
				     struct pbl_context *pbl)
{
	dma_addr_t dma_addr;

	dma_addr = dma_map_single(&dev->pdev->dev, pbl->pbl_buf,
				  pbl->pbl_buf_size_in_bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(&dev->pdev->dev, dma_addr)) {
		ibdev_err(&dev->ibdev, "Unable to map pbl to DMA address\n");
		return -ENOMEM;
	}

	pbl->phys.continuous.dma_addr = dma_addr;
	ibdev_dbg(&dev->ibdev,
		  "pbl continuous - dma_addr = %pad, size[%u]\n",
		  &dma_addr, pbl->pbl_buf_size_in_bytes);

	return 0;
}