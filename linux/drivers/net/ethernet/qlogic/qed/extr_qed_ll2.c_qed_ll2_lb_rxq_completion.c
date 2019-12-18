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
struct qed_ll2_info {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_LL2_RX_REGISTERED (struct qed_ll2_info*) ; 
 int qed_ll2_lb_rxq_handler (struct qed_hwfn*,struct qed_ll2_info*) ; 
 int /*<<< orphan*/  qed_ooo_submit_rx_buffers (struct qed_hwfn*,struct qed_ll2_info*) ; 
 int /*<<< orphan*/  qed_ooo_submit_tx_buffers (struct qed_hwfn*,struct qed_ll2_info*) ; 

__attribute__((used)) static int qed_ll2_lb_rxq_completion(struct qed_hwfn *p_hwfn, void *p_cookie)
{
	struct qed_ll2_info *p_ll2_conn = (struct qed_ll2_info *)p_cookie;
	int rc;

	if (!QED_LL2_RX_REGISTERED(p_ll2_conn))
		return 0;

	rc = qed_ll2_lb_rxq_handler(p_hwfn, p_ll2_conn);
	if (rc)
		return rc;

	qed_ooo_submit_rx_buffers(p_hwfn, p_ll2_conn);
	qed_ooo_submit_tx_buffers(p_hwfn, p_ll2_conn);

	return 0;
}