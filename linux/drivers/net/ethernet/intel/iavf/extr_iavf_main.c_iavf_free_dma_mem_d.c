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
struct iavf_hw {scalar_t__ back; } ;
struct iavf_dma_mem {scalar_t__ pa; int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;
struct iavf_adapter {TYPE_1__* pdev; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IAVF_ERR_PARAM ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum iavf_status iavf_free_dma_mem_d(struct iavf_hw *hw,
				     struct iavf_dma_mem *mem)
{
	struct iavf_adapter *adapter = (struct iavf_adapter *)hw->back;

	if (!mem || !mem->va)
		return IAVF_ERR_PARAM;
	dma_free_coherent(&adapter->pdev->dev, mem->size,
			  mem->va, (dma_addr_t)mem->pa);
	return 0;
}