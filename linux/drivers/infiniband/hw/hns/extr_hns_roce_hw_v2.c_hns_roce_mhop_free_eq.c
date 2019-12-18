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
struct hns_roce_eq {int entries; int eqe_size; int l0_last_num; int l1_last_num; int /*<<< orphan*/ * bt_l1; int /*<<< orphan*/ * l1_dma; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * buf_dma; int /*<<< orphan*/  l0_dma; int /*<<< orphan*/  bt_l0; } ;
struct TYPE_2__ {int eqe_hop_num; int eqe_buf_pg_sz; int eqe_ba_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_mhop_free_eq(struct hns_roce_dev *hr_dev,
				  struct hns_roce_eq *eq)
{
	struct device *dev = hr_dev->dev;
	u64 idx;
	u64 size;
	u32 buf_chk_sz;
	u32 bt_chk_sz;
	u32 mhop_num;
	int eqe_alloc;
	int i = 0;
	int j = 0;

	mhop_num = hr_dev->caps.eqe_hop_num;
	buf_chk_sz = 1 << (hr_dev->caps.eqe_buf_pg_sz + PAGE_SHIFT);
	bt_chk_sz = 1 << (hr_dev->caps.eqe_ba_pg_sz + PAGE_SHIFT);

	if (mhop_num == HNS_ROCE_HOP_NUM_0) {
		dma_free_coherent(dev, (unsigned int)(eq->entries *
				  eq->eqe_size), eq->bt_l0, eq->l0_dma);
		return;
	}

	dma_free_coherent(dev, bt_chk_sz, eq->bt_l0, eq->l0_dma);
	if (mhop_num == 1) {
		for (i = 0; i < eq->l0_last_num; i++) {
			if (i == eq->l0_last_num - 1) {
				eqe_alloc = i * (buf_chk_sz / eq->eqe_size);
				size = (eq->entries - eqe_alloc) * eq->eqe_size;
				dma_free_coherent(dev, size, eq->buf[i],
						  eq->buf_dma[i]);
				break;
			}
			dma_free_coherent(dev, buf_chk_sz, eq->buf[i],
					  eq->buf_dma[i]);
		}
	} else if (mhop_num == 2) {
		for (i = 0; i < eq->l0_last_num; i++) {
			dma_free_coherent(dev, bt_chk_sz, eq->bt_l1[i],
					  eq->l1_dma[i]);

			for (j = 0; j < bt_chk_sz / BA_BYTE_LEN; j++) {
				idx = i * (bt_chk_sz / BA_BYTE_LEN) + j;
				if ((i == eq->l0_last_num - 1)
				     && j == eq->l1_last_num - 1) {
					eqe_alloc = (buf_chk_sz / eq->eqe_size)
						    * idx;
					size = (eq->entries - eqe_alloc)
						* eq->eqe_size;
					dma_free_coherent(dev, size,
							  eq->buf[idx],
							  eq->buf_dma[idx]);
					break;
				}
				dma_free_coherent(dev, buf_chk_sz, eq->buf[idx],
						  eq->buf_dma[idx]);
			}
		}
	}
	kfree(eq->buf_dma);
	kfree(eq->buf);
	kfree(eq->l1_dma);
	kfree(eq->bt_l1);
	eq->buf_dma = NULL;
	eq->buf = NULL;
	eq->l1_dma = NULL;
	eq->bt_l1 = NULL;
}