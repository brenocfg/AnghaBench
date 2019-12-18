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
struct hns_roce_mtt {int order; int page_shift; int /*<<< orphan*/  mtt_type; int /*<<< orphan*/  first_seg; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HNS_ROCE_HEM_PAGE_SHIFT ; 
 int HNS_ROCE_MTT_ENTRY_PER_SEG ; 
 int hns_roce_alloc_mtt_range (struct hns_roce_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hns_roce_mtt_init(struct hns_roce_dev *hr_dev, int npages, int page_shift,
		      struct hns_roce_mtt *mtt)
{
	int ret;
	int i;

	/* Page num is zero, correspond to DMA memory register */
	if (!npages) {
		mtt->order = -1;
		mtt->page_shift = HNS_ROCE_HEM_PAGE_SHIFT;
		return 0;
	}

	/* Note: if page_shift is zero, FAST memory register */
	mtt->page_shift = page_shift;

	/* Compute MTT entry necessary */
	for (mtt->order = 0, i = HNS_ROCE_MTT_ENTRY_PER_SEG; i < npages;
	     i <<= 1)
		++mtt->order;

	/* Allocate MTT entry */
	ret = hns_roce_alloc_mtt_range(hr_dev, mtt->order, &mtt->first_seg,
				       mtt->mtt_type);
	if (ret == -1)
		return -ENOMEM;

	return 0;
}