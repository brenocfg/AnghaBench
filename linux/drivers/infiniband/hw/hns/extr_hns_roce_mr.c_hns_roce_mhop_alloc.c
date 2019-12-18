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
typedef  int u32 ;
struct hns_roce_mr {scalar_t__ type; int pbl_size; int pbl_hop_num; int pbl_ba_pg_sz; int /*<<< orphan*/ * pbl_l1_dma_addr; int /*<<< orphan*/ * pbl_bt_l1; int /*<<< orphan*/  pbl_buf_pg_sz; int /*<<< orphan*/  pbl_l0_dma_addr; int /*<<< orphan*/  pbl_ba; int /*<<< orphan*/  pbl_bt_l0; } ;
struct TYPE_2__ {int pbl_hop_num; int pbl_ba_pg_sz; int /*<<< orphan*/  pbl_buf_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 scalar_t__ MR_TYPE_FRMR ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int pbl_1hop_alloc (struct hns_roce_dev*,int,struct hns_roce_mr*,int) ; 
 scalar_t__ pbl_2hop_alloc (struct hns_roce_dev*,int,struct hns_roce_mr*,int) ; 
 scalar_t__ pbl_3hop_alloc (struct hns_roce_dev*,int,struct hns_roce_mr*,int) ; 

__attribute__((used)) static int hns_roce_mhop_alloc(struct hns_roce_dev *hr_dev, int npages,
			       struct hns_roce_mr *mr)
{
	struct device *dev = hr_dev->dev;
	u32 pbl_bt_sz;
	u32 mhop_num;

	mhop_num = (mr->type == MR_TYPE_FRMR ? 1 : hr_dev->caps.pbl_hop_num);
	pbl_bt_sz = 1 << (hr_dev->caps.pbl_ba_pg_sz + PAGE_SHIFT);

	if (mhop_num == HNS_ROCE_HOP_NUM_0)
		return 0;

	if (mhop_num == 1)
		return pbl_1hop_alloc(hr_dev, npages, mr, pbl_bt_sz);

	mr->pbl_l1_dma_addr = kcalloc(pbl_bt_sz / 8,
				      sizeof(*mr->pbl_l1_dma_addr),
				      GFP_KERNEL);
	if (!mr->pbl_l1_dma_addr)
		return -ENOMEM;

	mr->pbl_bt_l1 = kcalloc(pbl_bt_sz / 8, sizeof(*mr->pbl_bt_l1),
				GFP_KERNEL);
	if (!mr->pbl_bt_l1)
		goto err_kcalloc_bt_l1;

	/* alloc L0 BT */
	mr->pbl_bt_l0 = dma_alloc_coherent(dev, pbl_bt_sz,
					   &(mr->pbl_l0_dma_addr),
					   GFP_KERNEL);
	if (!mr->pbl_bt_l0)
		goto err_kcalloc_l2_dma;

	if (mhop_num == 2) {
		if (pbl_2hop_alloc(hr_dev, npages, mr, pbl_bt_sz))
			goto err_kcalloc_l2_dma;
	}

	if (mhop_num == 3) {
		if (pbl_3hop_alloc(hr_dev, npages, mr, pbl_bt_sz))
			goto err_kcalloc_l2_dma;
	}


	mr->pbl_size = npages;
	mr->pbl_ba = mr->pbl_l0_dma_addr;
	mr->pbl_hop_num = hr_dev->caps.pbl_hop_num;
	mr->pbl_ba_pg_sz = hr_dev->caps.pbl_ba_pg_sz;
	mr->pbl_buf_pg_sz = hr_dev->caps.pbl_buf_pg_sz;

	return 0;

err_kcalloc_l2_dma:
	kfree(mr->pbl_bt_l1);
	mr->pbl_bt_l1 = NULL;

err_kcalloc_bt_l1:
	kfree(mr->pbl_l1_dma_addr);
	mr->pbl_l1_dma_addr = NULL;

	return -ENOMEM;
}