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
struct ttm_dma_tt {int dummy; } ;
struct ttm_bo_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (unsigned long) ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ ttm_round_pot (int) ; 

size_t ttm_bo_dma_acc_size(struct ttm_bo_device *bdev,
			   unsigned long bo_size,
			   unsigned struct_size)
{
	unsigned npages = (PAGE_ALIGN(bo_size)) >> PAGE_SHIFT;
	size_t size = 0;

	size += ttm_round_pot(struct_size);
	size += ttm_round_pot(npages * (2*sizeof(void *) + sizeof(dma_addr_t)));
	size += ttm_round_pot(sizeof(struct ttm_dma_tt));
	return size;
}