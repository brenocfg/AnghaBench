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
struct rvt_qp {int s_flags; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  s_iowait; } ;

/* Variables and functions */
 int HFI1_S_ANY_WAIT_IO ; 
 int RVT_S_ANY_WAIT_SEND ; 
 int RVT_S_BUSY ; 
 int RVT_S_RESP_PENDING ; 
 int /*<<< orphan*/  iowait_get_ib_work (int /*<<< orphan*/ *) ; 
 scalar_t__ verbs_txreq_queued (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hfi1_send_ok(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	return !(qp->s_flags & (RVT_S_BUSY | HFI1_S_ANY_WAIT_IO)) &&
		(verbs_txreq_queued(iowait_get_ib_work(&priv->s_iowait)) ||
		(qp->s_flags & RVT_S_RESP_PENDING) ||
		 !(qp->s_flags & RVT_S_ANY_WAIT_SEND));
}