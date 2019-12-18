#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int map; struct hns_roce_link_table_entry* buf; } ;
struct hns_roce_link_table {int npages; int pg_sz; TYPE_2__ table; TYPE_3__* pg_list; } ;
struct hns_roce_v2_priv {struct hns_roce_link_table tpq; struct hns_roce_link_table tsq; } ;
struct hns_roce_link_table_entry {int blk_ba0; int blk_ba1_nxt_ptr; } ;
struct TYPE_5__ {int tsq_buf_pg_sz; int num_qps; int sl_num; int tpq_buf_pg_sz; int num_cqs; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; struct hns_roce_v2_priv* priv; } ;
struct device {int dummy; } ;
typedef  enum hns_roce_link_table_type { ____Placeholder_hns_roce_link_table_type } hns_roce_link_table_type ;
typedef  int dma_addr_t ;
struct TYPE_7__ {int map; struct hns_roce_link_table_entry* buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_LINK_TABLE_NXT_PTR_S ; 
 int PAGE_SHIFT ; 
#define  TPQ_LINK_TABLE 129 
#define  TSQ_LINK_TABLE 128 
 void* dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,struct hns_roce_link_table_entry*,int) ; 
 int hns_roce_config_link_table (struct hns_roce_dev*,int) ; 
 TYPE_3__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int max (int,int) ; 

__attribute__((used)) static int hns_roce_init_link_table(struct hns_roce_dev *hr_dev,
				    enum hns_roce_link_table_type type)
{
	struct hns_roce_v2_priv *priv = hr_dev->priv;
	struct hns_roce_link_table *link_tbl;
	struct hns_roce_link_table_entry *entry;
	struct device *dev = hr_dev->dev;
	u32 buf_chk_sz;
	dma_addr_t t;
	int func_num = 1;
	int pg_num_a;
	int pg_num_b;
	int pg_num;
	int size;
	int i;

	switch (type) {
	case TSQ_LINK_TABLE:
		link_tbl = &priv->tsq;
		buf_chk_sz = 1 << (hr_dev->caps.tsq_buf_pg_sz + PAGE_SHIFT);
		pg_num_a = hr_dev->caps.num_qps * 8 / buf_chk_sz;
		pg_num_b = hr_dev->caps.sl_num * 4 + 2;
		break;
	case TPQ_LINK_TABLE:
		link_tbl = &priv->tpq;
		buf_chk_sz = 1 << (hr_dev->caps.tpq_buf_pg_sz +	PAGE_SHIFT);
		pg_num_a = hr_dev->caps.num_cqs * 4 / buf_chk_sz;
		pg_num_b = 2 * 4 * func_num + 2;
		break;
	default:
		return -EINVAL;
	}

	pg_num = max(pg_num_a, pg_num_b);
	size = pg_num * sizeof(struct hns_roce_link_table_entry);

	link_tbl->table.buf = dma_alloc_coherent(dev, size,
						 &link_tbl->table.map,
						 GFP_KERNEL);
	if (!link_tbl->table.buf)
		goto out;

	link_tbl->pg_list = kcalloc(pg_num, sizeof(*link_tbl->pg_list),
				    GFP_KERNEL);
	if (!link_tbl->pg_list)
		goto err_kcalloc_failed;

	entry = link_tbl->table.buf;
	for (i = 0; i < pg_num; ++i) {
		link_tbl->pg_list[i].buf = dma_alloc_coherent(dev, buf_chk_sz,
							      &t, GFP_KERNEL);
		if (!link_tbl->pg_list[i].buf)
			goto err_alloc_buf_failed;

		link_tbl->pg_list[i].map = t;

		entry[i].blk_ba0 = (u32)(t >> 12);
		entry[i].blk_ba1_nxt_ptr = (u32)(t >> 44);

		if (i < (pg_num - 1))
			entry[i].blk_ba1_nxt_ptr |=
				(i + 1) << HNS_ROCE_LINK_TABLE_NXT_PTR_S;

	}
	link_tbl->npages = pg_num;
	link_tbl->pg_sz = buf_chk_sz;

	return hns_roce_config_link_table(hr_dev, type);

err_alloc_buf_failed:
	for (i -= 1; i >= 0; i--)
		dma_free_coherent(dev, buf_chk_sz,
				  link_tbl->pg_list[i].buf,
				  link_tbl->pg_list[i].map);
	kfree(link_tbl->pg_list);

err_kcalloc_failed:
	dma_free_coherent(dev, size, link_tbl->table.buf,
			  link_tbl->table.map);

out:
	return -ENOMEM;
}