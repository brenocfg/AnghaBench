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
typedef  scalar_t__ u32 ;
struct rvt_qp {scalar_t__ s_cur; scalar_t__ s_size; void* s_state; scalar_t__ s_psn; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {scalar_t__ s_tid_cur; } ;

/* Variables and functions */
 void* TID_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REQ ; 
 int /*<<< orphan*/  WRITE_RESP ; 
 scalar_t__ cmp_psn (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void update_qp_retry_state(struct rvt_qp *qp, u32 psn, u32 spsn,
				  u32 lpsn)
{
	struct hfi1_qp_priv *qpriv = qp->priv;

	qp->s_psn = psn + 1;
	/*
	 * If this is the first TID RDMA WRITE RESP packet for the current
	 * request, change the s_state so that the retry will be processed
	 * correctly. Similarly, if this is the last TID RDMA WRITE RESP
	 * packet, change the s_state and advance the s_cur.
	 */
	if (cmp_psn(psn, lpsn) >= 0) {
		qp->s_cur = qpriv->s_tid_cur + 1;
		if (qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		qp->s_state = TID_OP(WRITE_REQ);
	} else  if (!cmp_psn(psn, spsn)) {
		qp->s_cur = qpriv->s_tid_cur;
		qp->s_state = TID_OP(WRITE_RESP);
	}
}