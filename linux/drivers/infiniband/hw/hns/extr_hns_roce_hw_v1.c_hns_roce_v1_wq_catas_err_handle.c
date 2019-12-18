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
#define  HNS_ROCE_LWQCE_MTU_ERROR 134 
#define  HNS_ROCE_LWQCE_PORT_ERROR 133 
#define  HNS_ROCE_LWQCE_QPC_ERROR 132 
#define  HNS_ROCE_LWQCE_SL_ERROR 131 
#define  HNS_ROCE_LWQCE_SQ_WQE_SHIFT_ERROR 130 
#define  HNS_ROCE_LWQCE_WQE_ADDR_ERROR 129 
#define  HNS_ROCE_LWQCE_WQE_BA_ADDR_ERROR 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v1_wq_catas_err_handle(struct hns_roce_dev *hr_dev,
					    struct hns_roce_aeqe *aeqe, int qpn)
{
	struct device *dev = &hr_dev->pdev->dev;

	dev_warn(dev, "Local Work Queue Catastrophic Error.\n");
	switch (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) {
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
		dev_warn(dev, "QP %d, WQE shift error\n", qpn);
		break;
	case HNS_ROCE_LWQCE_SL_ERROR:
		dev_warn(dev, "QP %d, SL error.\n", qpn);
		break;
	case HNS_ROCE_LWQCE_PORT_ERROR:
		dev_warn(dev, "QP %d, port error.\n", qpn);
		break;
	default:
		break;
	}
}