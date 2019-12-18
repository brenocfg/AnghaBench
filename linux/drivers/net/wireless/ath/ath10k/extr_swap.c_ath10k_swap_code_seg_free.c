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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct ath10k_swap_code_seg_info {int /*<<< orphan*/ * paddr; int /*<<< orphan*/ * virt_address; TYPE_1__ seg_hw_info; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_swap_code_seg_free(struct ath10k *ar,
			  struct ath10k_swap_code_seg_info *seg_info)
{
	u32 seg_size;

	if (!seg_info)
		return;

	if (!seg_info->virt_address[0])
		return;

	seg_size = __le32_to_cpu(seg_info->seg_hw_info.size);
	dma_free_coherent(ar->dev, seg_size, seg_info->virt_address[0],
			  seg_info->paddr[0]);
}