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
struct io_pgtable_cfg {int /*<<< orphan*/  iommu_dev; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  __arm_lpae_dma_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __arm_lpae_sync_pte(arm_lpae_iopte *ptep,
				struct io_pgtable_cfg *cfg)
{
	dma_sync_single_for_device(cfg->iommu_dev, __arm_lpae_dma_addr(ptep),
				   sizeof(*ptep), DMA_TO_DEVICE);
}