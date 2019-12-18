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
struct TYPE_2__ {int type; } ;
union core_rx_cqe_union {TYPE_1__ rx_cqe_sp; } ;
typedef  scalar_t__ u16 ;
struct qed_ll2_rx_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  rcq_chain; int /*<<< orphan*/ * p_fw_cons; } ;
struct qed_ll2_info {struct qed_ll2_rx_queue rx_queue; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
#define  CORE_RX_CQE_TYPE_GSI_OFFLOAD 130 
#define  CORE_RX_CQE_TYPE_REGULAR 129 
#define  CORE_RX_CQE_TYPE_SLOW_PATH 128 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int EIO ; 
 int /*<<< orphan*/  QED_MSG_LL2 ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_consume (int /*<<< orphan*/ *) ; 
 scalar_t__ qed_chain_get_cons_idx (int /*<<< orphan*/ *) ; 
 int qed_ll2_handle_slowpath (struct qed_hwfn*,struct qed_ll2_info*,union core_rx_cqe_union*,unsigned long*) ; 
 int qed_ll2_rxq_handle_completion (struct qed_hwfn*,struct qed_ll2_info*,union core_rx_cqe_union*,unsigned long*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int qed_ll2_rxq_completion(struct qed_hwfn *p_hwfn, void *cookie)
{
	struct qed_ll2_info *p_ll2_conn = (struct qed_ll2_info *)cookie;
	struct qed_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	union core_rx_cqe_union *cqe = NULL;
	u16 cq_new_idx = 0, cq_old_idx = 0;
	unsigned long flags = 0;
	int rc = 0;

	spin_lock_irqsave(&p_rx->lock, flags);
	cq_new_idx = le16_to_cpu(*p_rx->p_fw_cons);
	cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);

	while (cq_new_idx != cq_old_idx) {
		bool b_last_cqe = (cq_new_idx == cq_old_idx);

		cqe =
		    (union core_rx_cqe_union *)
		    qed_chain_consume(&p_rx->rcq_chain);
		cq_old_idx = qed_chain_get_cons_idx(&p_rx->rcq_chain);

		DP_VERBOSE(p_hwfn,
			   QED_MSG_LL2,
			   "LL2 [sw. cons %04x, fw. at %04x] - Got Packet of type %02x\n",
			   cq_old_idx, cq_new_idx, cqe->rx_cqe_sp.type);

		switch (cqe->rx_cqe_sp.type) {
		case CORE_RX_CQE_TYPE_SLOW_PATH:
			rc = qed_ll2_handle_slowpath(p_hwfn, p_ll2_conn,
						     cqe, &flags);
			break;
		case CORE_RX_CQE_TYPE_GSI_OFFLOAD:
		case CORE_RX_CQE_TYPE_REGULAR:
			rc = qed_ll2_rxq_handle_completion(p_hwfn, p_ll2_conn,
							   cqe, &flags,
							   b_last_cqe);
			break;
		default:
			rc = -EIO;
		}
	}

	spin_unlock_irqrestore(&p_rx->lock, flags);
	return rc;
}