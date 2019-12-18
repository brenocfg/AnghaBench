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
struct hns_roce_eq {int cons_index; int /*<<< orphan*/  eqn; } ;
struct TYPE_10__ {int aeqe_depth; } ;
struct hns_roce_dev {TYPE_5__ caps; TYPE_1__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  ceqe; } ;
struct TYPE_7__ {int /*<<< orphan*/  out_param; int /*<<< orphan*/  status; int /*<<< orphan*/  token; } ;
struct TYPE_9__ {TYPE_3__ ce_event; TYPE_2__ cmd; } ;
struct hns_roce_aeqe {TYPE_4__ event; int /*<<< orphan*/  asyn; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_M ; 
 int /*<<< orphan*/  HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_S ; 
 int /*<<< orphan*/  HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M ; 
 int /*<<< orphan*/  HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S ; 
#define  HNS_ROCE_EVENT_TYPE_CEQ_OVERFLOW 144 
#define  HNS_ROCE_EVENT_TYPE_COMM_EST 143 
#define  HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR 142 
#define  HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID 141 
#define  HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW 140 
#define  HNS_ROCE_EVENT_TYPE_DB_OVERFLOW 139 
#define  HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR 138 
#define  HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR 137 
#define  HNS_ROCE_EVENT_TYPE_MB 136 
#define  HNS_ROCE_EVENT_TYPE_PATH_MIG 135 
#define  HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED 134 
#define  HNS_ROCE_EVENT_TYPE_PORT_CHANGE 133 
#define  HNS_ROCE_EVENT_TYPE_SQ_DRAINED 132 
#define  HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR 131 
#define  HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH 130 
#define  HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH 129 
#define  HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct hns_roce_aeqe*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  hns_roce_cmd_event (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_v1_cq_err_handle (struct hns_roce_dev*,struct hns_roce_aeqe*,int) ; 
 int /*<<< orphan*/  hns_roce_v1_db_overflow_handle (struct hns_roce_dev*,struct hns_roce_aeqe*) ; 
 int /*<<< orphan*/  hns_roce_v1_qp_err_handle (struct hns_roce_dev*,struct hns_roce_aeqe*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct hns_roce_aeqe* next_aeqe_sw_v1 (struct hns_roce_eq*) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_eq_cons_index_v1 (struct hns_roce_eq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v1_aeq_int(struct hns_roce_dev *hr_dev,
			       struct hns_roce_eq *eq)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_aeqe *aeqe;
	int aeqes_found = 0;
	int event_type;

	while ((aeqe = next_aeqe_sw_v1(eq))) {

		/* Make sure we read the AEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		dev_dbg(dev, "aeqe = %pK, aeqe->asyn.event_type = 0x%lx\n",
			aeqe,
			roce_get_field(aeqe->asyn,
				       HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M,
				       HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S));
		event_type = roce_get_field(aeqe->asyn,
					    HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M,
					    HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S);
		switch (event_type) {
		case HNS_ROCE_EVENT_TYPE_PATH_MIG:
			dev_warn(dev, "PATH MIG not supported\n");
			break;
		case HNS_ROCE_EVENT_TYPE_COMM_EST:
			dev_warn(dev, "COMMUNICATION established\n");
			break;
		case HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
			dev_warn(dev, "SQ DRAINED not supported\n");
			break;
		case HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
			dev_warn(dev, "PATH MIG failed\n");
			break;
		case HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		case HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		case HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
			hns_roce_v1_qp_err_handle(hr_dev, aeqe, event_type);
			break;
		case HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
		case HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
		case HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
			dev_warn(dev, "SRQ not support!\n");
			break;
		case HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		case HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
		case HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID:
			hns_roce_v1_cq_err_handle(hr_dev, aeqe, event_type);
			break;
		case HNS_ROCE_EVENT_TYPE_PORT_CHANGE:
			dev_warn(dev, "port change.\n");
			break;
		case HNS_ROCE_EVENT_TYPE_MB:
			hns_roce_cmd_event(hr_dev,
					   le16_to_cpu(aeqe->event.cmd.token),
					   aeqe->event.cmd.status,
					   le64_to_cpu(aeqe->event.cmd.out_param
					   ));
			break;
		case HNS_ROCE_EVENT_TYPE_DB_OVERFLOW:
			hns_roce_v1_db_overflow_handle(hr_dev, aeqe);
			break;
		case HNS_ROCE_EVENT_TYPE_CEQ_OVERFLOW:
			dev_warn(dev, "CEQ 0x%lx overflow.\n",
			roce_get_field(aeqe->event.ce_event.ceqe,
				     HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_M,
				     HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_S));
			break;
		default:
			dev_warn(dev, "Unhandled event %d on EQ %d at idx %u.\n",
				 event_type, eq->eqn, eq->cons_index);
			break;
		}

		eq->cons_index++;
		aeqes_found = 1;

		if (eq->cons_index > 2 * hr_dev->caps.aeqe_depth - 1) {
			dev_warn(dev, "cons_index overflow, set back to 0.\n");
			eq->cons_index = 0;
		}
	}

	set_eq_cons_index_v1(eq, 0);

	return aeqes_found;
}