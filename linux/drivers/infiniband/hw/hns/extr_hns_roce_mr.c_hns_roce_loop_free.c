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
typedef  size_t u64 ;
typedef  int u32 ;
struct hns_roce_mr {int /*<<< orphan*/  pbl_l0_dma_addr; int /*<<< orphan*/ * pbl_bt_l0; int /*<<< orphan*/ * pbl_l1_dma_addr; int /*<<< orphan*/ ** pbl_bt_l1; int /*<<< orphan*/ * pbl_l2_dma_addr; int /*<<< orphan*/ ** pbl_bt_l2; } ;
struct TYPE_2__ {int pbl_ba_pg_sz; int pbl_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_loop_free(struct hns_roce_dev *hr_dev,
			       struct hns_roce_mr *mr, int err_loop_index,
			       int loop_i, int loop_j)
{
	struct device *dev = hr_dev->dev;
	u32 mhop_num;
	u32 pbl_bt_sz;
	u64 bt_idx;
	int i, j;

	pbl_bt_sz = 1 << (hr_dev->caps.pbl_ba_pg_sz + PAGE_SHIFT);
	mhop_num = hr_dev->caps.pbl_hop_num;

	i = loop_i;
	if (mhop_num == 3 && err_loop_index == 2) {
		for (; i >= 0; i--) {
			dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l1[i],
					  mr->pbl_l1_dma_addr[i]);

			for (j = 0; j < pbl_bt_sz / BA_BYTE_LEN; j++) {
				if (i == loop_i && j >= loop_j)
					break;

				bt_idx = i * pbl_bt_sz / BA_BYTE_LEN + j;
				dma_free_coherent(dev, pbl_bt_sz,
						  mr->pbl_bt_l2[bt_idx],
						  mr->pbl_l2_dma_addr[bt_idx]);
			}
		}
	} else if (mhop_num == 3 && err_loop_index == 1) {
		for (i -= 1; i >= 0; i--) {
			dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l1[i],
					  mr->pbl_l1_dma_addr[i]);

			for (j = 0; j < pbl_bt_sz / BA_BYTE_LEN; j++) {
				bt_idx = i * pbl_bt_sz / BA_BYTE_LEN + j;
				dma_free_coherent(dev, pbl_bt_sz,
						  mr->pbl_bt_l2[bt_idx],
						  mr->pbl_l2_dma_addr[bt_idx]);
			}
		}
	} else if (mhop_num == 2 && err_loop_index == 1) {
		for (i -= 1; i >= 0; i--)
			dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l1[i],
					  mr->pbl_l1_dma_addr[i]);
	} else {
		dev_warn(dev, "not support: mhop_num=%d, err_loop_index=%d.",
			 mhop_num, err_loop_index);
		return;
	}

	dma_free_coherent(dev, pbl_bt_sz, mr->pbl_bt_l0, mr->pbl_l0_dma_addr);
	mr->pbl_bt_l0 = NULL;
	mr->pbl_l0_dma_addr = 0;
}