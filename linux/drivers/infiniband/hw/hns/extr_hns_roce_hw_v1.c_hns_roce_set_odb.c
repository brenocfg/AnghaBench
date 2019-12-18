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
 int /*<<< orphan*/  ROCEE_DB_OTHERS_WL_REG ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_M ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_S ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_M ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_set_odb(struct hns_roce_dev *hr_dev, u32 odb_alept,
			     u32 odb_alful)
{
	__le32 tmp;
	u32 val;

	/* Configure ODB */
	val = roce_read(hr_dev, ROCEE_DB_OTHERS_WL_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_M,
		       ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_S, odb_alful);
	roce_set_field(tmp, ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_M,
		       ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_S, odb_alept);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_DB_OTHERS_WL_REG, val);
}