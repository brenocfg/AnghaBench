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
typedef  scalar_t__ u32 ;
struct hns_roce_db_table {TYPE_2__* ext_db; } ;
struct hns_roce_v1_priv {struct hns_roce_db_table db_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {struct TYPE_4__* sdb_buf_list; void* map; void* buf; struct TYPE_4__* odb_buf_list; void* eodb_dep; void* esdb_dep; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_ODB_ALEPT ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_ODB_ALFUL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_ODB_DEPTH ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_ODB_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_SDB_ALEPT ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_SDB_ALFUL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_SDB_DEPTH ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_SDB_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_ODB_ALEPT ; 
 int /*<<< orphan*/  HNS_ROCE_V1_ODB_ALFUL ; 
 int /*<<< orphan*/  HNS_ROCE_V1_SDB_ALEPT ; 
 int /*<<< orphan*/  HNS_ROCE_V1_SDB_ALFUL ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  hns_roce_set_db_ext_mode (struct hns_roce_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hns_roce_set_odb (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_set_odb_ext (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_set_sdb (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_set_sdb_ext (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_db_ext_init(struct hns_roce_dev *hr_dev, u32 sdb_ext_mod,
				u32 odb_ext_mod)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_db_table *db;
	dma_addr_t sdb_dma_addr;
	dma_addr_t odb_dma_addr;
	int ret = 0;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	db = &priv->db_table;

	db->ext_db = kmalloc(sizeof(*db->ext_db), GFP_KERNEL);
	if (!db->ext_db)
		return -ENOMEM;

	if (sdb_ext_mod) {
		db->ext_db->sdb_buf_list = kmalloc(
				sizeof(*db->ext_db->sdb_buf_list), GFP_KERNEL);
		if (!db->ext_db->sdb_buf_list) {
			ret = -ENOMEM;
			goto ext_sdb_buf_fail_out;
		}

		db->ext_db->sdb_buf_list->buf = dma_alloc_coherent(dev,
						     HNS_ROCE_V1_EXT_SDB_SIZE,
						     &sdb_dma_addr, GFP_KERNEL);
		if (!db->ext_db->sdb_buf_list->buf) {
			ret = -ENOMEM;
			goto alloc_sq_db_buf_fail;
		}
		db->ext_db->sdb_buf_list->map = sdb_dma_addr;

		db->ext_db->esdb_dep = ilog2(HNS_ROCE_V1_EXT_SDB_DEPTH);
		hns_roce_set_sdb_ext(hr_dev, HNS_ROCE_V1_EXT_SDB_ALEPT,
				     HNS_ROCE_V1_EXT_SDB_ALFUL);
	} else
		hns_roce_set_sdb(hr_dev, HNS_ROCE_V1_SDB_ALEPT,
				 HNS_ROCE_V1_SDB_ALFUL);

	if (odb_ext_mod) {
		db->ext_db->odb_buf_list = kmalloc(
				sizeof(*db->ext_db->odb_buf_list), GFP_KERNEL);
		if (!db->ext_db->odb_buf_list) {
			ret = -ENOMEM;
			goto ext_odb_buf_fail_out;
		}

		db->ext_db->odb_buf_list->buf = dma_alloc_coherent(dev,
						     HNS_ROCE_V1_EXT_ODB_SIZE,
						     &odb_dma_addr, GFP_KERNEL);
		if (!db->ext_db->odb_buf_list->buf) {
			ret = -ENOMEM;
			goto alloc_otr_db_buf_fail;
		}
		db->ext_db->odb_buf_list->map = odb_dma_addr;

		db->ext_db->eodb_dep = ilog2(HNS_ROCE_V1_EXT_ODB_DEPTH);
		hns_roce_set_odb_ext(hr_dev, HNS_ROCE_V1_EXT_ODB_ALEPT,
				     HNS_ROCE_V1_EXT_ODB_ALFUL);
	} else
		hns_roce_set_odb(hr_dev, HNS_ROCE_V1_ODB_ALEPT,
				 HNS_ROCE_V1_ODB_ALFUL);

	hns_roce_set_db_ext_mode(hr_dev, sdb_ext_mod, odb_ext_mod);

	return 0;

alloc_otr_db_buf_fail:
	kfree(db->ext_db->odb_buf_list);

ext_odb_buf_fail_out:
	if (sdb_ext_mod) {
		dma_free_coherent(dev, HNS_ROCE_V1_EXT_SDB_SIZE,
				  db->ext_db->sdb_buf_list->buf,
				  db->ext_db->sdb_buf_list->map);
	}

alloc_sq_db_buf_fail:
	if (sdb_ext_mod)
		kfree(db->ext_db->sdb_buf_list);

ext_sdb_buf_fail_out:
	kfree(db->ext_db);
	return ret;
}