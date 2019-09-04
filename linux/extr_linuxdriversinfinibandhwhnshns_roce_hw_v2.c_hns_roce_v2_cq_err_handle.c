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
#define  HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR 129 
#define  HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW 128 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cq_event (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_roce_v2_cq_err_handle(struct hns_roce_dev *hr_dev,
				      struct hns_roce_aeqe *aeqe,
				      int event_type, u32 cqn)
{
	struct device *dev = hr_dev->dev;

	switch (event_type) {
	case HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		dev_warn(dev, "CQ 0x%x access err.\n", cqn);
		break;
	case HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
		dev_warn(dev, "CQ 0x%x overflow\n", cqn);
		break;
	default:
		break;
	}

	hns_roce_cq_event(hr_dev, cqn, event_type);
}