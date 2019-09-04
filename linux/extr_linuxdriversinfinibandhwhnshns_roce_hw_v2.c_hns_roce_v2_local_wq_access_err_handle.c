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
typedef  int u32 ;
struct hns_roce_dev {struct device* dev; } ;
struct hns_roce_aeqe {int /*<<< orphan*/  asyn; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  HNS_ROCE_LAVWQE_KEY_STATE_ERROR 134 
#define  HNS_ROCE_LAVWQE_LENGTH_ERROR 133 
#define  HNS_ROCE_LAVWQE_MR_OPERATION_ERROR 132 
#define  HNS_ROCE_LAVWQE_PD_ERROR 131 
#define  HNS_ROCE_LAVWQE_RW_ACC_ERROR 130 
#define  HNS_ROCE_LAVWQE_R_KEY_VIOLATION 129 
#define  HNS_ROCE_LAVWQE_VA_ERROR 128 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v2_local_wq_access_err_handle(struct hns_roce_dev *hr_dev,
					    struct hns_roce_aeqe *aeqe, u32 qpn)
{
	struct device *dev = hr_dev->dev;
	int sub_type;

	dev_warn(dev, "Local access violation work queue error.\n");
	sub_type = roce_get_field(aeqe->asyn, HNS_ROCE_V2_AEQE_SUB_TYPE_M,
				  HNS_ROCE_V2_AEQE_SUB_TYPE_S);
	switch (sub_type) {
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
		dev_err(dev, "Unhandled sub_event type %d.\n", sub_type);
		break;
	}
}