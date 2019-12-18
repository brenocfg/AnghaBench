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
struct hns_roce_eq {int entries; int eqe_size; int l0_last_num; int l1_last_num; scalar_t__** buf_dma; scalar_t__** buf; scalar_t__** l1_dma; scalar_t__** bt_l1; scalar_t__ l0_dma; scalar_t__* bt_l0; scalar_t__ nxt_eqe_ba; scalar_t__ cur_eqe_ba; } ;
struct TYPE_2__ {int eqe_hop_num; int eqe_buf_pg_sz; int eqe_ba_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BA_BYTE_LEN ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_HOP_NUM_0 ; 
 int PAGE_ALIGN (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,scalar_t__*,scalar_t__) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__**) ; 

__attribute__((used)) static int hns_roce_mhop_alloc_eq(struct hns_roce_dev *hr_dev,
				  struct hns_roce_eq *eq)
{
	struct device *dev = hr_dev->dev;
	int eq_alloc_done = 0;
	int eq_buf_cnt = 0;
	int eqe_alloc;
	u32 buf_chk_sz;
	u32 bt_chk_sz;
	u32 mhop_num;
	u64 size;
	u64 idx;
	int ba_num;
	int bt_num;
	int record_i;
	int record_j;
	int i = 0;
	int j = 0;

	mhop_num = hr_dev->caps.eqe_hop_num;
	buf_chk_sz = 1 << (hr_dev->caps.eqe_buf_pg_sz + PAGE_SHIFT);
	bt_chk_sz = 1 << (hr_dev->caps.eqe_ba_pg_sz + PAGE_SHIFT);

	ba_num = DIV_ROUND_UP(PAGE_ALIGN(eq->entries * eq->eqe_size),
			      buf_chk_sz);
	bt_num = DIV_ROUND_UP(ba_num, bt_chk_sz / BA_BYTE_LEN);

	if (mhop_num == HNS_ROCE_HOP_NUM_0) {
		if (eq->entries > buf_chk_sz / eq->eqe_size) {
			dev_err(dev, "eq entries %d is larger than buf_pg_sz!",
				eq->entries);
			return -EINVAL;
		}
		eq->bt_l0 = dma_alloc_coherent(dev, eq->entries * eq->eqe_size,
					       &(eq->l0_dma), GFP_KERNEL);
		if (!eq->bt_l0)
			return -ENOMEM;

		eq->cur_eqe_ba = eq->l0_dma;
		eq->nxt_eqe_ba = 0;

		return 0;
	}

	eq->buf_dma = kcalloc(ba_num, sizeof(*eq->buf_dma), GFP_KERNEL);
	if (!eq->buf_dma)
		return -ENOMEM;
	eq->buf = kcalloc(ba_num, sizeof(*eq->buf), GFP_KERNEL);
	if (!eq->buf)
		goto err_kcalloc_buf;

	if (mhop_num == 2) {
		eq->l1_dma = kcalloc(bt_num, sizeof(*eq->l1_dma), GFP_KERNEL);
		if (!eq->l1_dma)
			goto err_kcalloc_l1_dma;

		eq->bt_l1 = kcalloc(bt_num, sizeof(*eq->bt_l1), GFP_KERNEL);
		if (!eq->bt_l1)
			goto err_kcalloc_bt_l1;
	}

	/* alloc L0 BT */
	eq->bt_l0 = dma_alloc_coherent(dev, bt_chk_sz, &eq->l0_dma, GFP_KERNEL);
	if (!eq->bt_l0)
		goto err_dma_alloc_l0;

	if (mhop_num == 1) {
		if (ba_num > (bt_chk_sz / BA_BYTE_LEN))
			dev_err(dev, "ba_num %d is too large for 1 hop\n",
				ba_num);

		/* alloc buf */
		for (i = 0; i < bt_chk_sz / BA_BYTE_LEN; i++) {
			if (eq_buf_cnt + 1 < ba_num) {
				size = buf_chk_sz;
			} else {
				eqe_alloc = i * (buf_chk_sz / eq->eqe_size);
				size = (eq->entries - eqe_alloc) * eq->eqe_size;
			}
			eq->buf[i] = dma_alloc_coherent(dev, size,
							&(eq->buf_dma[i]),
							GFP_KERNEL);
			if (!eq->buf[i])
				goto err_dma_alloc_buf;

			*(eq->bt_l0 + i) = eq->buf_dma[i];

			eq_buf_cnt++;
			if (eq_buf_cnt >= ba_num)
				break;
		}
		eq->cur_eqe_ba = eq->buf_dma[0];
		if (ba_num > 1)
			eq->nxt_eqe_ba = eq->buf_dma[1];

	} else if (mhop_num == 2) {
		/* alloc L1 BT and buf */
		for (i = 0; i < bt_chk_sz / BA_BYTE_LEN; i++) {
			eq->bt_l1[i] = dma_alloc_coherent(dev, bt_chk_sz,
							  &(eq->l1_dma[i]),
							  GFP_KERNEL);
			if (!eq->bt_l1[i])
				goto err_dma_alloc_l1;
			*(eq->bt_l0 + i) = eq->l1_dma[i];

			for (j = 0; j < bt_chk_sz / BA_BYTE_LEN; j++) {
				idx = i * bt_chk_sz / BA_BYTE_LEN + j;
				if (eq_buf_cnt + 1 < ba_num) {
					size = buf_chk_sz;
				} else {
					eqe_alloc = (buf_chk_sz / eq->eqe_size)
						    * idx;
					size = (eq->entries - eqe_alloc)
						* eq->eqe_size;
				}
				eq->buf[idx] = dma_alloc_coherent(dev, size,
								  &(eq->buf_dma[idx]),
								  GFP_KERNEL);
				if (!eq->buf[idx])
					goto err_dma_alloc_buf;

				*(eq->bt_l1[i] + j) = eq->buf_dma[idx];

				eq_buf_cnt++;
				if (eq_buf_cnt >= ba_num) {
					eq_alloc_done = 1;
					break;
				}
			}

			if (eq_alloc_done)
				break;
		}
		eq->cur_eqe_ba = eq->buf_dma[0];
		if (ba_num > 1)
			eq->nxt_eqe_ba = eq->buf_dma[1];
	}

	eq->l0_last_num = i + 1;
	if (mhop_num == 2)
		eq->l1_last_num = j + 1;

	return 0;

err_dma_alloc_l1:
	dma_free_coherent(dev, bt_chk_sz, eq->bt_l0, eq->l0_dma);
	eq->bt_l0 = NULL;
	eq->l0_dma = 0;
	for (i -= 1; i >= 0; i--) {
		dma_free_coherent(dev, bt_chk_sz, eq->bt_l1[i],
				  eq->l1_dma[i]);

		for (j = 0; j < bt_chk_sz / BA_BYTE_LEN; j++) {
			idx = i * bt_chk_sz / BA_BYTE_LEN + j;
			dma_free_coherent(dev, buf_chk_sz, eq->buf[idx],
					  eq->buf_dma[idx]);
		}
	}
	goto err_dma_alloc_l0;

err_dma_alloc_buf:
	dma_free_coherent(dev, bt_chk_sz, eq->bt_l0, eq->l0_dma);
	eq->bt_l0 = NULL;
	eq->l0_dma = 0;

	if (mhop_num == 1)
		for (i -= 1; i >= 0; i--)
			dma_free_coherent(dev, buf_chk_sz, eq->buf[i],
					  eq->buf_dma[i]);
	else if (mhop_num == 2) {
		record_i = i;
		record_j = j;
		for (; i >= 0; i--) {
			dma_free_coherent(dev, bt_chk_sz, eq->bt_l1[i],
					  eq->l1_dma[i]);

			for (j = 0; j < bt_chk_sz / BA_BYTE_LEN; j++) {
				if (i == record_i && j >= record_j)
					break;

				idx = i * bt_chk_sz / BA_BYTE_LEN + j;
				dma_free_coherent(dev, buf_chk_sz,
						  eq->buf[idx],
						  eq->buf_dma[idx]);
			}
		}
	}

err_dma_alloc_l0:
	kfree(eq->bt_l1);
	eq->bt_l1 = NULL;

err_kcalloc_bt_l1:
	kfree(eq->l1_dma);
	eq->l1_dma = NULL;

err_kcalloc_l1_dma:
	kfree(eq->buf);
	eq->buf = NULL;

err_kcalloc_buf:
	kfree(eq->buf_dma);
	eq->buf_dma = NULL;

	return -ENOMEM;
}