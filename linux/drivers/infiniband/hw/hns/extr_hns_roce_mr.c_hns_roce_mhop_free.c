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
typedef  int u64 ;
typedef  int u32 ;
struct hns_roce_mr {int pbl_size; scalar_t__ type; int l0_chunk_last_num; int l1_chunk_last_num; int /*<<< orphan*/ * pbl_l2_dma_addr; int /*<<< orphan*/ * pbl_bt_l2; int /*<<< orphan*/ * pbl_l1_dma_addr; int /*<<< orphan*/ * pbl_bt_l1; int /*<<< orphan*/  pbl_l0_dma_addr; int /*<<< orphan*/  pbl_bt_l0; int /*<<< orphan*/  pbl_dma_addr; int /*<<< orphan*/  pbl_buf; } ;
struct TYPE_2__ {int pbl_ba_pg_sz; int pbl_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 scalar_t__ MR_TYPE_FRMR ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_mhop_free(struct hns_roce_dev *hr_dev,
			       struct hns_roce_mr *mr)
{
	struct device *dev = hr_dev->dev;
	int npages_allocated;
	int npages;
	int i, j;
	u32 pbl_bt_sz;
	u32 mhop_num;
	u64 bt_idx;

	npages = mr->pbl_size;
	pbl_bt_sz = 1 << (hr_dev->caps.pbl_ba_pg_sz + PAGE_SHIFT);
	mhop_num = (mr->type == MR_TYPE_FRMR) ? 1 : hr_dev->caps.pbl_hop_num;

	if (mhop_num == HNS_ROCE_HOP_NUM_0)
		return;

	if (mhop_num == 1) {
		dma_free_coherent(dev, (unsigned int)(npages * BA_BYTE_LEN),
				  mr->pbl_buf, mr->pbl_dma_addr);
		return;
	}

	dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l0,
			  mr->pbl_l0_dma_addr);

	if (mhop_num == 2) {
		for (i = 0; i < mr->l0_chunk_last_num; i++) {
			if (i == mr->l0_chunk_last_num - 1) {
				npages_allocated =
						i * (pbl_bt_sz / BA_BYTE_LEN);

				dma_free_coherent(dev,
				      (npages - npages_allocated) * BA_BYTE_LEN,
				       mr->pbl_bt_l1[i],
				       mr->pbl_l1_dma_addr[i]);

				break;
			}

			dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l1[i],
					  mr->pbl_l1_dma_addr[i]);
		}
	} else if (mhop_num == 3) {
		for (i = 0; i < mr->l0_chunk_last_num; i++) {
			dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l1[i],
					  mr->pbl_l1_dma_addr[i]);

			for (j = 0; j < pbl_bt_sz / BA_BYTE_LEN; j++) {
				bt_idx = i * (pbl_bt_sz / BA_BYTE_LEN) + j;

				if ((i == mr->l0_chunk_last_num - 1)
				    && j == mr->l1_chunk_last_num - 1) {
					npages_allocated = bt_idx *
						      (pbl_bt_sz / BA_BYTE_LEN);

					dma_free_coherent(dev,
					      (npages - npages_allocated) *
					      BA_BYTE_LEN,
					      mr->pbl_bt_l2[bt_idx],
					      mr->pbl_l2_dma_addr[bt_idx]);

					break;
				}

				dma_free_coherent(dev, pbl_bt_sz,
						mr->pbl_bt_l2[bt_idx],
						mr->pbl_l2_dma_addr[bt_idx]);
			}
		}
	}

	kfree(mr->pbl_bt_l1);
	kfree(mr->pbl_l1_dma_addr);
	mr->pbl_bt_l1 = NULL;
	mr->pbl_l1_dma_addr = NULL;
	if (mhop_num == 3) {
		kfree(mr->pbl_bt_l2);
		kfree(mr->pbl_l2_dma_addr);
		mr->pbl_bt_l2 = NULL;
		mr->pbl_l2_dma_addr = NULL;
	}
}