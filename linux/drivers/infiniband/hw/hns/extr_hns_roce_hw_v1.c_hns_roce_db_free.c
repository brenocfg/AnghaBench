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
struct hns_roce_db_table {TYPE_2__* ext_db; scalar_t__ odb_ext_mod; scalar_t__ sdb_ext_mod; } ;
struct hns_roce_v1_priv {struct hns_roce_db_table db_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* odb_buf_list; int /*<<< orphan*/  map; int /*<<< orphan*/  buf; struct TYPE_4__* sdb_buf_list; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_ODB_SIZE ; 
 int /*<<< orphan*/  HNS_ROCE_V1_EXT_SDB_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void hns_roce_db_free(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_db_table *db;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	db = &priv->db_table;

	if (db->sdb_ext_mod) {
		dma_free_coherent(dev, HNS_ROCE_V1_EXT_SDB_SIZE,
				  db->ext_db->sdb_buf_list->buf,
				  db->ext_db->sdb_buf_list->map);
		kfree(db->ext_db->sdb_buf_list);
	}

	if (db->odb_ext_mod) {
		dma_free_coherent(dev, HNS_ROCE_V1_EXT_ODB_SIZE,
				  db->ext_db->odb_buf_list->buf,
				  db->ext_db->odb_buf_list->map);
		kfree(db->ext_db->odb_buf_list);
	}

	kfree(db->ext_db);
}