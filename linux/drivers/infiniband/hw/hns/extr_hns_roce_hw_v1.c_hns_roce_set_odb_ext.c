#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_db_table {TYPE_3__* ext_db; } ;
struct hns_roce_v1_priv {struct hns_roce_db_table db_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  eodb_dep; TYPE_2__* odb_buf_list; } ;
struct TYPE_5__ {int map; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCEE_EXT_DB_OTHERS_WL_EMPTY_REG ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_OTHERS_WL_REG ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_M ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_S ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_OTH_H_REG ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_OTH_REG ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_M ; 
 int /*<<< orphan*/  ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_set_odb_ext(struct hns_roce_dev *hr_dev, u32 ext_odb_alept,
				 u32 ext_odb_alful)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_db_table *db;
	dma_addr_t odb_dma_addr;
	__le32 tmp;
	u32 val;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	db = &priv->db_table;

	/* Configure extend ODB threshold */
	roce_write(hr_dev, ROCEE_EXT_DB_OTHERS_WL_EMPTY_REG, ext_odb_alept);
	roce_write(hr_dev, ROCEE_EXT_DB_OTHERS_WL_REG, ext_odb_alful);

	/* Configure extend ODB base addr */
	odb_dma_addr = db->ext_db->odb_buf_list->map;
	roce_write(hr_dev, ROCEE_EXT_DB_OTH_REG, (u32)(odb_dma_addr >> 12));

	/* Configure extend ODB depth */
	val = roce_read(hr_dev, ROCEE_EXT_DB_OTH_H_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_M,
		       ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_S,
		       db->ext_db->eodb_dep);
	roce_set_field(tmp, ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_M,
		       ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_S,
		       db->ext_db->eodb_dep);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_EXT_DB_OTH_H_REG, val);

	dev_dbg(dev, "ext ODB depth: 0x%x\n", db->ext_db->eodb_dep);
	dev_dbg(dev, "ext ODB threshold: empty: 0x%x, ful: 0x%x\n",
		ext_odb_alept, ext_odb_alful);
}