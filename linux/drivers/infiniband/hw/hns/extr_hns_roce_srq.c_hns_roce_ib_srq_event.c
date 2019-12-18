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
struct ib_srq {int /*<<< orphan*/  srq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct ib_srq* srq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
struct hns_roce_srq {int /*<<< orphan*/  srqn; struct ib_srq ibsrq; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
typedef  enum hns_roce_event { ____Placeholder_hns_roce_event } hns_roce_event ;

/* Variables and functions */
#define  HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR 129 
#define  HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH 128 
 int /*<<< orphan*/  IB_EVENT_SRQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_SRQ_LIMIT_REACHED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_ib_srq_event(struct hns_roce_srq *srq,
				  enum hns_roce_event event_type)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(srq->ibsrq.device);
	struct ib_srq *ibsrq = &srq->ibsrq;
	struct ib_event event;

	if (ibsrq->event_handler) {
		event.device      = ibsrq->device;
		event.element.srq = ibsrq;
		switch (event_type) {
		case HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			break;
		case HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
			event.event = IB_EVENT_SRQ_ERR;
			break;
		default:
			dev_err(hr_dev->dev,
			   "hns_roce:Unexpected event type 0x%x on SRQ %06lx\n",
			   event_type, srq->srqn);
			return;
		}

		ibsrq->event_handler(&event, ibsrq->srq_context);
	}
}