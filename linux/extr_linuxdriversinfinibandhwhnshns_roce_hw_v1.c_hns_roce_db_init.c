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
typedef  void* u32 ;
struct hns_roce_db_table {void* odb_ext_mod; void* sdb_ext_mod; } ;
struct hns_roce_v1_priv {struct hns_roce_db_table db_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 void* HNS_ROCE_ODB_EXTEND_MODE ; 
 void* HNS_ROCE_ODB_POLL_MODE ; 
 void* HNS_ROCE_SDB_EXTEND_MODE ; 
 void* HNS_ROCE_SDB_NORMAL_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_db_ext_init (struct hns_roce_dev*,void*,void*) ; 
 int /*<<< orphan*/  hns_roce_set_db_event_mode (struct hns_roce_dev*,void*,void*) ; 
 int /*<<< orphan*/  memset (struct hns_roce_db_table*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_roce_db_init(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_db_table *db;
	u32 sdb_ext_mod;
	u32 odb_ext_mod;
	u32 sdb_evt_mod;
	u32 odb_evt_mod;
	int ret = 0;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	db = &priv->db_table;

	memset(db, 0, sizeof(*db));

	/* Default DB mode */
	sdb_ext_mod = HNS_ROCE_SDB_EXTEND_MODE;
	odb_ext_mod = HNS_ROCE_ODB_EXTEND_MODE;
	sdb_evt_mod = HNS_ROCE_SDB_NORMAL_MODE;
	odb_evt_mod = HNS_ROCE_ODB_POLL_MODE;

	db->sdb_ext_mod = sdb_ext_mod;
	db->odb_ext_mod = odb_ext_mod;

	/* Init extend DB */
	ret = hns_roce_db_ext_init(hr_dev, sdb_ext_mod, odb_ext_mod);
	if (ret) {
		dev_err(dev, "Failed in extend DB configuration.\n");
		return ret;
	}

	hns_roce_set_db_event_mode(hr_dev, sdb_evt_mod, odb_evt_mod);

	return 0;
}