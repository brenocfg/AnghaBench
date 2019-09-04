#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ROCEE_GLB_CFG_REG ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_ROCEE_DB_OTH_MODE_S ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_ROCEE_DB_SQ_MODE_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_set_db_event_mode(struct hns_roce_dev *hr_dev,
				       int sdb_mode, int odb_mode)
{
	__le32 tmp;
	u32 val;

	val = roce_read(hr_dev, ROCEE_GLB_CFG_REG);
	tmp = cpu_to_le32(val);
	roce_set_bit(tmp, ROCEE_GLB_CFG_ROCEE_DB_SQ_MODE_S, sdb_mode);
	roce_set_bit(tmp, ROCEE_GLB_CFG_ROCEE_DB_OTH_MODE_S, odb_mode);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_GLB_CFG_REG, val);
}