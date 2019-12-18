#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct hns_roce_eq {int cons_index; int event_type; int sub_type; int entries; int /*<<< orphan*/  eqn; } ;
struct hns_roce_dev {struct device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  out_param; int /*<<< orphan*/  status; int /*<<< orphan*/  token; } ;
struct TYPE_8__ {int /*<<< orphan*/  srq; } ;
struct TYPE_7__ {int /*<<< orphan*/  cq; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp; } ;
struct TYPE_10__ {TYPE_4__ cmd; TYPE_3__ srq_event; TYPE_2__ cq_event; TYPE_1__ qp_event; } ;
struct hns_roce_aeqe {TYPE_5__ event; int /*<<< orphan*/  asyn; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  HNS_ROCE_EVENT_TYPE_CEQ_OVERFLOW 143 
#define  HNS_ROCE_EVENT_TYPE_COMM_EST 142 
#define  HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR 141 
#define  HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW 140 
#define  HNS_ROCE_EVENT_TYPE_DB_OVERFLOW 139 
#define  HNS_ROCE_EVENT_TYPE_FLR 138 
#define  HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR 137 
#define  HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR 136 
#define  HNS_ROCE_EVENT_TYPE_MB 135 
#define  HNS_ROCE_EVENT_TYPE_PATH_MIG 134 
#define  HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED 133 
#define  HNS_ROCE_EVENT_TYPE_SQ_DRAINED 132 
#define  HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR 131 
#define  HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH 130 
#define  HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH 129 
#define  HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR 128 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_M ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_S ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_EVENT_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_EVENT_TYPE_S ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_V2_AEQE_SUB_TYPE_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  hns_roce_cmd_event (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cq_event (struct hns_roce_dev*,void*,int) ; 
 int /*<<< orphan*/  hns_roce_qp_event (struct hns_roce_dev*,void*,int) ; 
 int /*<<< orphan*/  hns_roce_srq_event (struct hns_roce_dev*,void*,int) ; 
 int /*<<< orphan*/  hns_roce_v2_init_irq_work (struct hns_roce_dev*,struct hns_roce_eq*,void*,void*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct hns_roce_aeqe* next_aeqe_sw_v2 (struct hns_roce_eq*) ; 
 void* roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_eq_cons_index_v2 (struct hns_roce_eq*) ; 

__attribute__((used)) static int hns_roce_v2_aeq_int(struct hns_roce_dev *hr_dev,
			       struct hns_roce_eq *eq)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_aeqe *aeqe = next_aeqe_sw_v2(eq);
	int aeqe_found = 0;
	int event_type;
	int sub_type;
	u32 srqn;
	u32 qpn;
	u32 cqn;

	while (aeqe) {
		/* Make sure we read AEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		event_type = roce_get_field(aeqe->asyn,
					    HNS_ROCE_V2_AEQE_EVENT_TYPE_M,
					    HNS_ROCE_V2_AEQE_EVENT_TYPE_S);
		sub_type = roce_get_field(aeqe->asyn,
					  HNS_ROCE_V2_AEQE_SUB_TYPE_M,
					  HNS_ROCE_V2_AEQE_SUB_TYPE_S);
		qpn = roce_get_field(aeqe->event.qp_event.qp,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_M,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_S);
		cqn = roce_get_field(aeqe->event.cq_event.cq,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_M,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_S);
		srqn = roce_get_field(aeqe->event.srq_event.srq,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_M,
				     HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_S);

		switch (event_type) {
		case HNS_ROCE_EVENT_TYPE_PATH_MIG:
		case HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
		case HNS_ROCE_EVENT_TYPE_COMM_EST:
		case HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
		case HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		case HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
		case HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		case HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
			hns_roce_qp_event(hr_dev, qpn, event_type);
			break;
		case HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
		case HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
			hns_roce_srq_event(hr_dev, srqn, event_type);
			break;
		case HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		case HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
			hns_roce_cq_event(hr_dev, cqn, event_type);
			break;
		case HNS_ROCE_EVENT_TYPE_DB_OVERFLOW:
			break;
		case HNS_ROCE_EVENT_TYPE_MB:
			hns_roce_cmd_event(hr_dev,
					le16_to_cpu(aeqe->event.cmd.token),
					aeqe->event.cmd.status,
					le64_to_cpu(aeqe->event.cmd.out_param));
			break;
		case HNS_ROCE_EVENT_TYPE_CEQ_OVERFLOW:
			break;
		case HNS_ROCE_EVENT_TYPE_FLR:
			break;
		default:
			dev_err(dev, "Unhandled event %d on EQ %d at idx %u.\n",
				event_type, eq->eqn, eq->cons_index);
			break;
		}

		eq->event_type = event_type;
		eq->sub_type = sub_type;
		++eq->cons_index;
		aeqe_found = 1;

		if (eq->cons_index > (2 * eq->entries - 1))
			eq->cons_index = 0;

		hns_roce_v2_init_irq_work(hr_dev, eq, qpn, cqn);

		aeqe = next_aeqe_sw_v2(eq);
	}

	set_eq_cons_index_v2(eq);
	return aeqe_found;
}