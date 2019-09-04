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
struct hns_roce_dev {struct device* dev; } ;
struct hns_roce_aeqe {int /*<<< orphan*/  asyn; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  HNS_ROCE_LWQCE_MTU_ERROR 132 
#define  HNS_ROCE_LWQCE_QPC_ERROR 131 
#define  HNS_ROCE_LWQCE_SQ_WQE_SHIFT_ERROR 130 
#define  HNS_ROCE_LWQCE_WQE_ADDR_ERROR 129 
#define  HNS_ROCE_LWQCE_WQE_BA_ADDR_ERROR 128 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v2_wq_catas_err_handle(struct hns_roce_dev *hr_dev,
						  struct hns_roce_aeqe *aeqe,
						  u32 qpn)
{
	struct device *dev = hr_dev->dev;
	int sub_type;

	dev_warn(dev, "Local work queue catastrophic error.\n");
	sub_type = roce_get_field(aeqe->asyn, HNS_ROCE_V2_AEQE_SUB_TYPE_M,
				  HNS_ROCE_V2_AEQE_SUB_TYPE_S);
	switch (sub_type) {
	case HNS_ROCE_LWQCE_QPC_ERROR:
		dev_warn(dev, "QP %d, QPC error.\n", qpn);
		break;
	case HNS_ROCE_LWQCE_MTU_ERROR:
		dev_warn(dev, "QP %d, MTU error.\n", qpn);
		break;
	case HNS_ROCE_LWQCE_WQE_BA_ADDR_ERROR:
		dev_warn(dev, "QP %d, WQE BA addr error.\n", qpn);
		break;
	case HNS_ROCE_LWQCE_WQE_ADDR_ERROR:
		dev_warn(dev, "QP %d, WQE addr error.\n", qpn);
		break;
	case HNS_ROCE_LWQCE_SQ_WQE_SHIFT_ERROR:
		dev_warn(dev, "QP %d, WQE shift error.\n", qpn);
		break;
	default:
		dev_err(dev, "Unhandled sub_event type %d.\n", sub_type);
		break;
	}
}