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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tx_list (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_del_tid_reap_timer (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_del_tid_retry_timer (struct rvt_qp*) ; 
 int /*<<< orphan*/  iowait_sdma_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_pio_drain (struct rvt_qp*) ; 

void quiesce_qp(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	hfi1_del_tid_reap_timer(qp);
	hfi1_del_tid_retry_timer(qp);
	iowait_sdma_drain(&priv->s_iowait);
	qp_pio_drain(qp);
	flush_tx_list(qp);
}