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
#define  HNS_ROCE_LAVWQE_KEY_STATE_ERROR 134 
#define  HNS_ROCE_LAVWQE_LENGTH_ERROR 133 
#define  HNS_ROCE_LAVWQE_MR_OPERATION_ERROR 132 
#define  HNS_ROCE_LAVWQE_PD_ERROR 131 
#define  HNS_ROCE_LAVWQE_RW_ACC_ERROR 130 
#define  HNS_ROCE_LAVWQE_R_KEY_VIOLATION 129 
#define  HNS_ROCE_LAVWQE_VA_ERROR 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v1_local_wq_access_err_handle(struct hns_roce_dev *hr_dev,
						   struct hns_roce_aeqe *aeqe,
						   int qpn)
{
	struct device *dev = &hr_dev->pdev->dev;

	dev_warn(dev, "Local Access Violation Work Queue Error.\n");
	switch (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) {
	case HNS_ROCE_LAVWQE_R_KEY_VIOLATION:
		dev_warn(dev, "QP %d, R_key violation.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_LENGTH_ERROR:
		dev_warn(dev, "QP %d, length error.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_VA_ERROR:
		dev_warn(dev, "QP %d, VA error.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_PD_ERROR:
		dev_err(dev, "QP %d, PD error.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_RW_ACC_ERROR:
		dev_warn(dev, "QP %d, rw acc error.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_KEY_STATE_ERROR:
		dev_warn(dev, "QP %d, key state error.\n", qpn);
		break;
	case HNS_ROCE_LAVWQE_MR_OPERATION_ERROR:
		dev_warn(dev, "QP %d, MR operation error.\n", qpn);
		break;
	default:
		break;
	}
}