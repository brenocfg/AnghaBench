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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40evf_adapter {TYPE_1__* pdev; } ;
struct i40e_hw {scalar_t__ back; } ;
struct i40e_dma_mem {scalar_t__ va; int /*<<< orphan*/  pa; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40E_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

i40e_status i40evf_allocate_dma_mem_d(struct i40e_hw *hw,
				      struct i40e_dma_mem *mem,
				      u64 size, u32 alignment)
{
	struct i40evf_adapter *adapter = (struct i40evf_adapter *)hw->back;

	if (!mem)
		return I40E_ERR_PARAM;

	mem->size = ALIGN(size, alignment);
	mem->va = dma_alloc_coherent(&adapter->pdev->dev, mem->size,
				     (dma_addr_t *)&mem->pa, GFP_KERNEL);
	if (mem->va)
		return 0;
	else
		return I40E_ERR_NO_MEMORY;
}