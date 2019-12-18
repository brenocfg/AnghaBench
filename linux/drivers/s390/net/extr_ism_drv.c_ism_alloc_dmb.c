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
struct smcd_dmb {unsigned long sba_idx; scalar_t__ cpu_addr; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dmb_len; } ;
struct ism_dev {int /*<<< orphan*/  sba_bitmap; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 unsigned long ISM_DMB_BIT_OFFSET ; 
 unsigned long ISM_NR_DMBS ; 
 scalar_t__ PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int __GFP_COMP ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dma_get_max_seg_size (int /*<<< orphan*/ *) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ism_alloc_dmb(struct ism_dev *ism, struct smcd_dmb *dmb)
{
	unsigned long bit;

	if (PAGE_ALIGN(dmb->dmb_len) > dma_get_max_seg_size(&ism->pdev->dev))
		return -EINVAL;

	if (!dmb->sba_idx) {
		bit = find_next_zero_bit(ism->sba_bitmap, ISM_NR_DMBS,
					 ISM_DMB_BIT_OFFSET);
		if (bit == ISM_NR_DMBS)
			return -ENOMEM;

		dmb->sba_idx = bit;
	}
	if (dmb->sba_idx < ISM_DMB_BIT_OFFSET ||
	    test_and_set_bit(dmb->sba_idx, ism->sba_bitmap))
		return -EINVAL;

	dmb->cpu_addr = dma_alloc_coherent(&ism->pdev->dev, dmb->dmb_len,
					   &dmb->dma_addr,
					   GFP_KERNEL | __GFP_NOWARN | __GFP_NOMEMALLOC | __GFP_COMP | __GFP_NORETRY);
	if (!dmb->cpu_addr)
		clear_bit(dmb->sba_idx, ism->sba_bitmap);

	return dmb->cpu_addr ? 0 : -ENOMEM;
}