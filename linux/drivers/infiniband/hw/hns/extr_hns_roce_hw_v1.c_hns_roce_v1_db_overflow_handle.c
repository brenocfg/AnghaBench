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
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct hns_roce_aeqe {int /*<<< orphan*/  asyn; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S ; 
#define  HNS_ROCE_DB_SUBTYPE_ODB_ALM_EMP 133 
#define  HNS_ROCE_DB_SUBTYPE_ODB_ALM_OVF 132 
#define  HNS_ROCE_DB_SUBTYPE_ODB_OVF 131 
#define  HNS_ROCE_DB_SUBTYPE_SDB_ALM_EMP 130 
#define  HNS_ROCE_DB_SUBTYPE_SDB_ALM_OVF 129 
#define  HNS_ROCE_DB_SUBTYPE_SDB_OVF 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v1_db_overflow_handle(struct hns_roce_dev *hr_dev,
					   struct hns_roce_aeqe *aeqe)
{
	struct device *dev = &hr_dev->pdev->dev;

	switch (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) {
	case HNS_ROCE_DB_SUBTYPE_SDB_OVF:
		dev_warn(dev, "SDB overflow.\n");
		break;
	case HNS_ROCE_DB_SUBTYPE_SDB_ALM_OVF:
		dev_warn(dev, "SDB almost overflow.\n");
		break;
	case HNS_ROCE_DB_SUBTYPE_SDB_ALM_EMP:
		dev_warn(dev, "SDB almost empty.\n");
		break;
	case HNS_ROCE_DB_SUBTYPE_ODB_OVF:
		dev_warn(dev, "ODB overflow.\n");
		break;
	case HNS_ROCE_DB_SUBTYPE_ODB_ALM_OVF:
		dev_warn(dev, "ODB almost overflow.\n");
		break;
	case HNS_ROCE_DB_SUBTYPE_ODB_ALM_EMP:
		dev_warn(dev, "SDB almost empty.\n");
		break;
	default:
		break;
	}
}