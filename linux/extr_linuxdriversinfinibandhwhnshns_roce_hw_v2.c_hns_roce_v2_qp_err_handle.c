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
struct hns_roce_aeqe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  HNS_ROCE_EVENT_TYPE_COMM_EST 132 
#define  HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR 131 
#define  HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR 130 
#define  HNS_ROCE_EVENT_TYPE_SQ_DRAINED 129 
#define  HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  hns_roce_qp_event (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_roce_v2_local_wq_access_err_handle (struct hns_roce_dev*,struct hns_roce_aeqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_v2_wq_catas_err_handle (struct hns_roce_dev*,struct hns_roce_aeqe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v2_qp_err_handle(struct hns_roce_dev *hr_dev,
				      struct hns_roce_aeqe *aeqe,
				      int event_type, u32 qpn)
{
	struct device *dev = hr_dev->dev;

	switch (event_type) {
	case HNS_ROCE_EVENT_TYPE_COMM_EST:
		dev_warn(dev, "Communication established.\n");
		break;
	case HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
		dev_warn(dev, "Send queue drained.\n");
		break;
	case HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		hns_roce_v2_wq_catas_err_handle(hr_dev, aeqe, qpn);
		break;
	case HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		dev_warn(dev, "Invalid request local work queue error.\n");
		break;
	case HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
		hns_roce_v2_local_wq_access_err_handle(hr_dev, aeqe, qpn);
		break;
	default:
		break;
	}

	hns_roce_qp_event(hr_dev, qpn, event_type);
}