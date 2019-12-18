#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qed_ptt {int dummy; } ;
struct TYPE_7__ {scalar_t__ conn_type; } ;
struct TYPE_6__ {int b_cb_registered; int /*<<< orphan*/  rx_sb_index; } ;
struct TYPE_5__ {int b_cb_registered; int /*<<< orphan*/  tx_sb_index; } ;
struct qed_ll2_info {TYPE_3__ input; TYPE_2__ rx_queue; TYPE_1__ tx_queue; } ;
struct qed_hwfn {TYPE_4__* cdev; int /*<<< orphan*/  p_ooo_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_FCOE ; 
 int /*<<< orphan*/  ETH_P_FIP ; 
 scalar_t__ QED_LL2_RX_REGISTERED (struct qed_ll2_info*) ; 
 scalar_t__ QED_LL2_TX_REGISTERED (struct qed_ll2_info*) ; 
 scalar_t__ QED_LL2_TYPE_FCOE ; 
 scalar_t__ QED_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  QED_LLH_FILTER_ETHERTYPE ; 
 int /*<<< orphan*/  QED_MF_UFP_SPECIFIC ; 
 int /*<<< orphan*/  qed_int_unregister_cb (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 struct qed_ll2_info* qed_ll2_handle_sanity_lock (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_rxq_flush (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_txq_flush (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_llh_remove_protocol_filter (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_release_all_isles (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_sp_ll2_rx_queue_stop (struct qed_hwfn*,struct qed_ll2_info*) ; 
 int qed_sp_ll2_tx_queue_stop (struct qed_hwfn*,struct qed_ll2_info*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_ll2_terminate_connection(void *cxt, u8 connection_handle)
{
	struct qed_hwfn *p_hwfn = cxt;
	struct qed_ll2_info *p_ll2_conn = NULL;
	int rc = -EINVAL;
	struct qed_ptt *p_ptt;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return -EAGAIN;

	p_ll2_conn = qed_ll2_handle_sanity_lock(p_hwfn, connection_handle);
	if (!p_ll2_conn) {
		rc = -EINVAL;
		goto out;
	}

	/* Stop Tx & Rx of connection, if needed */
	if (QED_LL2_TX_REGISTERED(p_ll2_conn)) {
		p_ll2_conn->tx_queue.b_cb_registered = false;
		smp_wmb(); /* Make sure this is seen by ll2_lb_rxq_completion */
		rc = qed_sp_ll2_tx_queue_stop(p_hwfn, p_ll2_conn);
		if (rc)
			goto out;

		qed_ll2_txq_flush(p_hwfn, connection_handle);
		qed_int_unregister_cb(p_hwfn, p_ll2_conn->tx_queue.tx_sb_index);
	}

	if (QED_LL2_RX_REGISTERED(p_ll2_conn)) {
		p_ll2_conn->rx_queue.b_cb_registered = false;
		smp_wmb(); /* Make sure this is seen by ll2_lb_rxq_completion */
		rc = qed_sp_ll2_rx_queue_stop(p_hwfn, p_ll2_conn);
		if (rc)
			goto out;

		qed_ll2_rxq_flush(p_hwfn, connection_handle);
		qed_int_unregister_cb(p_hwfn, p_ll2_conn->rx_queue.rx_sb_index);
	}

	if (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO)
		qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);

	if (p_ll2_conn->input.conn_type == QED_LL2_TYPE_FCOE) {
		if (!test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
			qed_llh_remove_protocol_filter(p_hwfn->cdev, 0,
						       QED_LLH_FILTER_ETHERTYPE,
						       ETH_P_FCOE, 0);
		qed_llh_remove_protocol_filter(p_hwfn->cdev, 0,
					       QED_LLH_FILTER_ETHERTYPE,
					       ETH_P_FIP, 0);
	}

out:
	qed_ptt_release(p_hwfn, p_ptt);
	return rc;
}