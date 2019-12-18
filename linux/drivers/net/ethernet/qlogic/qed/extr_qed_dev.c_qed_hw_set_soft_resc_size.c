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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ BDQ_NUM_RESOURCES ; 
 int EINVAL ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 scalar_t__ MAX_NUM_LL2_RX_QUEUES ; 
 scalar_t__ NUM_OF_GLOBAL_QUEUES ; 
#define  QED_BDQ 131 
 int QED_IS_AH (int /*<<< orphan*/ ) ; 
#define  QED_LL2_QUEUE 130 
 int QED_MAX_RESC ; 
#define  QED_RDMA_CNQ_RAM 129 
#define  QED_RDMA_STATS_QUEUE 128 
 scalar_t__ RDMA_NUM_STATISTIC_COUNTERS_BB ; 
 scalar_t__ RDMA_NUM_STATISTIC_COUNTERS_K2 ; 
 int __qed_hw_set_soft_resc_size (struct qed_hwfn*,struct qed_ptt*,int,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int
qed_hw_set_soft_resc_size(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	bool b_ah = QED_IS_AH(p_hwfn->cdev);
	u32 resc_max_val, mcp_resp;
	u8 res_id;
	int rc;

	for (res_id = 0; res_id < QED_MAX_RESC; res_id++) {
		switch (res_id) {
		case QED_LL2_QUEUE:
			resc_max_val = MAX_NUM_LL2_RX_QUEUES;
			break;
		case QED_RDMA_CNQ_RAM:
			/* No need for a case for QED_CMDQS_CQS since
			 * CNQ/CMDQS are the same resource.
			 */
			resc_max_val = NUM_OF_GLOBAL_QUEUES;
			break;
		case QED_RDMA_STATS_QUEUE:
			resc_max_val = b_ah ? RDMA_NUM_STATISTIC_COUNTERS_K2
			    : RDMA_NUM_STATISTIC_COUNTERS_BB;
			break;
		case QED_BDQ:
			resc_max_val = BDQ_NUM_RESOURCES;
			break;
		default:
			continue;
		}

		rc = __qed_hw_set_soft_resc_size(p_hwfn, p_ptt, res_id,
						 resc_max_val, &mcp_resp);
		if (rc)
			return rc;

		/* There's no point to continue to the next resource if the
		 * command is not supported by the MFW.
		 * We do continue if the command is supported but the resource
		 * is unknown to the MFW. Such a resource will be later
		 * configured with the default allocation values.
		 */
		if (mcp_resp == FW_MSG_CODE_UNSUPPORTED)
			return -EINVAL;
	}

	return 0;
}