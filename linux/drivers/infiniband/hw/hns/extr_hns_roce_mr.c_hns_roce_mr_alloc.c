#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  void* u32 ;
struct hns_roce_mr {unsigned long long iova; unsigned long long size; int /*<<< orphan*/ * pbl_buf; scalar_t__ pbl_dma_addr; scalar_t__ pbl_l0_dma_addr; int /*<<< orphan*/ * pbl_l1_dma_addr; int /*<<< orphan*/ * pbl_l2_dma_addr; int /*<<< orphan*/ * pbl_bt_l0; int /*<<< orphan*/ * pbl_bt_l1; int /*<<< orphan*/ * pbl_bt_l2; int /*<<< orphan*/  key; scalar_t__ enabled; void* access; void* pd; } ;
struct TYPE_4__ {int /*<<< orphan*/  pbl_hop_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtpt_bitmap; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__ mr_table; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int hns_roce_bitmap_alloc (int /*<<< orphan*/ *,unsigned long*) ; 
 int hns_roce_mhop_alloc (struct hns_roce_dev*,int,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  hw_index_to_key (unsigned long) ; 

__attribute__((used)) static int hns_roce_mr_alloc(struct hns_roce_dev *hr_dev, u32 pd, u64 iova,
			     u64 size, u32 access, int npages,
			     struct hns_roce_mr *mr)
{
	struct device *dev = hr_dev->dev;
	unsigned long index = 0;
	int ret;

	/* Allocate a key for mr from mr_table */
	ret = hns_roce_bitmap_alloc(&hr_dev->mr_table.mtpt_bitmap, &index);
	if (ret == -1)
		return -ENOMEM;

	mr->iova = iova;			/* MR va starting addr */
	mr->size = size;			/* MR addr range */
	mr->pd = pd;				/* MR num */
	mr->access = access;			/* MR access permit */
	mr->enabled = 0;			/* MR active status */
	mr->key = hw_index_to_key(index);	/* MR key */

	if (size == ~0ull) {
		mr->pbl_buf = NULL;
		mr->pbl_dma_addr = 0;
		/* PBL multi-hop addressing parameters */
		mr->pbl_bt_l2 = NULL;
		mr->pbl_bt_l1 = NULL;
		mr->pbl_bt_l0 = NULL;
		mr->pbl_l2_dma_addr = NULL;
		mr->pbl_l1_dma_addr = NULL;
		mr->pbl_l0_dma_addr = 0;
	} else {
		if (!hr_dev->caps.pbl_hop_num) {
			mr->pbl_buf = dma_alloc_coherent(dev,
							 npages * BA_BYTE_LEN,
							 &(mr->pbl_dma_addr),
							 GFP_KERNEL);
			if (!mr->pbl_buf)
				return -ENOMEM;
		} else {
			ret = hns_roce_mhop_alloc(hr_dev, npages, mr);
		}
	}

	return ret;
}